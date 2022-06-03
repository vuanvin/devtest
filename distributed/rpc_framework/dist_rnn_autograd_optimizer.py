import torch
import torch.nn as nn

class EmbeddingTable(nn.Module):
    r"""
    Encoding layers of the RNNModel
    """
    def __init__(self, ntoken, ninp, dropout):
        super(EmbeddingTable, self).__init__()
        self.drop = nn.Dropout(dropout)
        self.encoder = nn.Embedding(ntoken, ninp).cuda()
        self.encoder.weight.data.uniform_(-0.1, 0.1)

    def forward(self, input):
        return self.drop(self.encoder(input.cuda()).cpu()


class Decoder(nn.Module):
    def __init__(self, ntoken, nhid, dropout):
        super(Decoder, self).__init__()
        self.drop = nn.Dropout(dropout)
        self.decoder = nn.Linear(nhid, ntoken)
        self.decoder.bias.data.zero_()
        self.decoder.weight.data.uniform_(-0.1, 0.1)

    def forward(self, output):
        return self.decoder(self.drop(output))


def _parameter_rrefs(module):
    param_rrefs = []
    for param in module.parameters():
        param_rrefs.append(RRef(param))
    return param_rrefs


class RNNModel(nn.Module):
    def __init__(self, ps, ntoken, ninp, nhid, nlayers, dropout=0.5):
        super(RNNModel, self).__init__()

        # setup embedding table remotely
        self.emb_table_rref = rpc.remote(ps, EmbeddingTable, args=(ntoken, ninp, dropout))
        # setup LSTM locally
        self.rnn = nn.LSTM(ninp, nhid, nlayers, dropout=dropout)
        # setup decoder remotely
        self.decoder_rref = rpc.remote(ps, Decoder, args=(ntoken, nhid, dropout))

    def forward(self, input, hidden):
        # pass input to the remote embedding table and fetch emb tensor back
        emb = _remote_method(EmbeddingTable.forward, self.emb_table_rref, input)
        output, hidden = self.rnn(emb, hidden)
        # pass output to the rremote decoder and get the decoded output back
        decoded = _remote_method(Decoder.forward, self.decoder_rref, output)
        return decoded, hidden

    def parameter_rrefs(self):
        remote_params = []
        # get RRefs of embedding table
        remote_params.extend(_remote_method(_parameter_rrefs, self.emb_table_rref))
        # create RRefs for local parameters
        remote_params.extend(_parameter_rrefs(self.rnn))
        # get RRefs of decoder
        remote_params.extend(_remote_method(_parameter_rrefs, self.decoder_rref))
        return remote_params


def run_trainer():
    batch = 5
    ntoken = 10
    ninp = 2

    nhid = 3
    nindices = 3
    nlayers = 4
    hidden = (
        torch.randn(nlayers, nindices, nhid),
        torch.randn(nlayers, nindices, nhid)
    )

    model = rnn.RNNModel('ps', ntoken, ninp, nhid, nlayers)

    # setup distributed optimizer
    opt = DistributedOptimizer(
        optim.SGD,
        model.parameter_rrefs(),
        lr=0.05,
    )

    criterion = torch.nn.CrossEntropyLoss()

    def get_next_batch():
        for _ in range(5):
            data = torch.LongTensor(batch, nindices) % ntoken
            target = torch.LongTensor(batch, ntoken) % nindices
            yield data, target

    # train for 10 iterations
    for epoch in range(10):
        for data, target in get_next_batch():
            # create distributed autograd context
            with dist_autograd.context() as context_id:
                hidden[0].detach_()
                hidden[1].detach_()
                output, hidden = model(data, hidden)
                loss = criterion(output, target)
                # run distributed backward pass
                dist_autograd.backward(context_id, [loss])
                # run distributed optimizer
                opt.step(context_id)
                # not necessary to zero grads since they are
                # accumulated into the distributed autograd context
                # which is reset every iteration.
        print("Training epoch {}".format(epoch))


def run_worker(rank, world_size):
    os.environ['MASTER_ADDR'] = 'localhost'
    os.environ['MASTER_PORT'] = '29500'
    if rank == 1:
        rpc.init_rpc("trainer", rank=rank, world_size=world_size)
        # _run_trainer()
        run_trainer()
    else:
        rpc.init_rpc("ps", rank=rank, world_size=world_size)
        # parameter server do nothing
        pass

    # block until all rpcs finish
    rpc.shutdown()


if __name__=="__main__":
    world_size = 2
    mp.spawn(run_worker, args=(world_size, ), nprocs=world_size, join=True)