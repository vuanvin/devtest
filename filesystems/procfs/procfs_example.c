// #include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define MODULE_VERS "1.0"
#define MODULE_NAME "procfs_example"
#define FOOBAR_LEN 10

struct fb_data_t {
    char name[FOOBAR_LEN + 1];
    char value[FOOBAR_LEN + 1];
} foo_data;

char global_buf[100];

static struct proc_dir_entry *example_dir, *foo_file;

static int proc_foo_open(struct inode* inode, struct file *file) {
    return 0;
}

static ssize_t proc_foo_read(struct file* file, char __user* buf, size_t count, loff_t* pos)
{
    struct fb_data_t* fb_data = (struct fb_data_t*)file->private_data;
    int len = sprintf(global_buf, "%s = '%s'\n", fb_data->name, fb_data->value);
    copy_to_user(buf, global_buf, len);
    return len;
}

static ssize_t proc_foo_write(struct file* file, const char __user* buf, size_t count, loff_t* pos)
{
    struct fb_data_t* fb_data = (struct fb_data_t*)file->private_data;
    int len = count <= FOOBAR_LEN ? count : FOOBAR_LEN;

    if (copy_from_user(fb_data->name, buf, len))
        return -EFAULT;
    fb_data->value[len] = '\0';

    return len;
}

static struct proc_ops proc_foo_fops = {
    .proc_open =    proc_foo_open,
    .proc_write =   proc_foo_write,
    .proc_read =    proc_foo_read,
};

static int __init procfs_example_init(void)
{
    int ret = 0;
    /* create directory */
    example_dir = proc_mkdir(MODULE_NAME, NULL);
    if (example_dir == NULL) {
        return -ENOMEM;
    }

    /* create file */
    foo_file = proc_create_data("foo", 0644, example_dir, &proc_foo_fops, &foo_data);
    if (foo_file == NULL) {
        ret = -ENOMEM;
        goto no_foo;
    }

    strcpy(foo_data.name, "fooname");
    strcpy(foo_data.value, "foovalue");

    /* everything OK */
    printk(KERN_INFO "%s %s initialized\n", MODULE_NAME, MODULE_VERS);
    return 0;

no_foo:
    remove_proc_entry("jiffies", example_dir);

    return 0;
}

static void __exit procfs_example_exit(void)
{
    remove_proc_entry("foo", example_dir);
    remove_proc_entry(MODULE_NAME, NULL);

    printk(KERN_INFO "%s %s removed\n", MODULE_NAME, MODULE_VERS);
}

module_init(procfs_example_init);
module_exit(procfs_example_exit);

MODULE_AUTHOR("Yuanyin Zhang");
MODULE_DESCRIPTION("procfs example");
MODULE_LICENSE("GPL");