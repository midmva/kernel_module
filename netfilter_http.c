#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/tcp.h>

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int


MODULE_AUTHOR("Miruk Dmitry <midv@tut.by>");
MODULE_DESCRIPTION("Module for test task");
MODULE_LICENSE("GPL");



struct nf_hook_ops bundle;

unsigned int hookFunc(uint hooknum,
                  struct sk_buff *skb,
                  const struct net_device *in,
                  const struct net_device *out,
                  int (*okfn)(struct sk_buff *)  )
{
    struct iphdr *ip;
    char array[3];

    if (skb->protocol == htons(ETH_P_IP))
    {
        ip = (struct iphdr *)skb_network_header(skb);
        if (ip->version == 4 && ip->protocol == IPPROTO_TCP)
        {
            skb_set_transport_header(skb, ip->ihl * 4);
            memcpy(array,skb->data+sizeof(struct ethhdr)+sizeof(struct iphdr)+sizeof(struct tcphdr)-2,3);
            if (array[0] == 'G'&&array[1] == 'E'&&array[2] == 'T'){
                //printk("%c%c%c",array[0],array[1],array[2]);
                return NF_DROP;
            }
        }
    }
    return NF_ACCEPT;
}

int init(void)
{
    printk(KERN_INFO "NetFilter:Init filter\n");

    bundle.hook = hookFunc;
    bundle.pf = PF_INET;
    bundle.hooknum = NF_INET_LOCAL_OUT;
    bundle.priority = NF_IP_PRI_FIRST;

    nf_register_hook(&bundle);
    return 0;
}

void exit(void)
{
    nf_unregister_hook(&bundle);
    printk(KERN_INFO "NetFilter:Exit test module\n");
}



module_init(init);
module_exit(exit);
