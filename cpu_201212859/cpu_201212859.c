#include <linux/module.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>



static int meminfo_proc_show(struct seq_file *m, void *v)
{
	struct task_struct *task;

	for_each_process(task){
		seq_printf(m,"{datos:201212859 Anicka Cercado CentOS 7.0 ,nombre:\"%s\",pid:%d,estado:%li}\n",
			task->comm, 
			task->pid, 
			task->state
		);
	}
	return 0;
}

static int meminfo_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, meminfo_proc_show, NULL);
}


static const struct file_operations meminfo_proc_fops = {
	.open		= meminfo_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init ex_init(void)
{
	proc_create("cpu_201212859", 0, NULL, &meminfo_proc_fops);
	printk(KERN_INFO "Anicka Cercado\n");
	return 0;

}

static void __exit ex_fini(void)
{
	remove_proc_entry("cpu_201212859", NULL);
	printk(KERN_INFO "Sistemas Operativos 1\n");
	return;
}

module_init(ex_init);
module_exit(ex_fini);
MODULE_LICENSE("GPL");
