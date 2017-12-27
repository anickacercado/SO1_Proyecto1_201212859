#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/hugetlb.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/proc_fs.h>
#include <linux/quicklist.h>
#include <linux/seq_file.h>
#include <linux/swap.h>
#include <linux/vmstat.h>
#include <linux/vmalloc.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <linux/module.h>


static int meminfo_proc_show(struct seq_file *m, void *v)
{
	struct sysinfo i;
	unsigned long committed;
	long available;
	unsigned long pagecache;
	unsigned long wmark_low = 0;
	unsigned long pages[NR_LRU_LISTS];
	int lru;

	long total; 
	long free; 
	long percent;

	#define K(x) ((x) << (PAGE_SHIFT - 10))
	si_meminfo(&i);
	committed = percpu_counter_read_positive(&vm_committed_as);


	for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
		pages[lru] = global_page_state(NR_LRU_BASE + lru);

	available = i.freeram - wmark_low;

	pagecache = pages[LRU_ACTIVE_FILE] + pages[LRU_INACTIVE_FILE];
	pagecache -= min(pagecache / 2, wmark_low);
	available += pagecache;

	available += global_page_state(NR_SLAB_RECLAIMABLE) -
		     min(global_page_state(NR_SLAB_RECLAIMABLE) / 2, wmark_low);

	if (available < 0)
		available = 0;


	total = K(i.totalram);
	free = K(i.freeram);
	percent = total - free;	

	
	seq_printf(m,
		"{datos:201212859 Anicka Cercado CentOS 7.0 ,RAM_total:%8lu KB,RAM_libre:%8lu KB,RAM_utilizada:%8lu KB}\n" //en kB
		,
		total,
		free,
		percent
		);

	return 0;
#undef K
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

static int __init proc_meminfo_init(void)
{
	proc_create("memo_201212859", 0, NULL, &meminfo_proc_fops);
	printk (KERN_INFO "\n201212859\n");
	return 0;
}

static void __exit mymodule_exit(void)
{
	remove_proc_entry("memo_201212859", NULL);
	printk(KERN_INFO "\nSistemas Operativos 1\n");
	return;
}

module_init(proc_meminfo_init);
module_exit(mymodule_exit);

MODULE_LICENSE("GPL");
