#include <fcntl.h>
#include <linux/cn_proc.h>
#include <linux/connector.h>
#include <linux/netlink.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct {
  struct nlmsghdr nlh;
  struct cn_msg cn_msg;
  struct proc_event proc_ev;
} msg;

struct {
  struct nlmsghdr nlh;
  struct cn_msg cn_msg;
  enum proc_cn_mcast_op op;
} sub_msg;

int main(int argc, char** argv)
{

  int sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_CONNECTOR);

  struct sockaddr_nl addr;
  memset(&addr, 0, sizeof(addr));
  addr.nl_family = AF_NETLINK;
  addr.nl_groups = CN_IDX_PROC;
  addr.nl_pid = getpid();

  if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind");
    close(sock);
    exit(EXIT_FAILURE);
  }

  memset(&sub_msg, 0, sizeof(sub_msg));
  sub_msg.nlh.nlmsg_len = sizeof(sub_msg);
  sub_msg.nlh.nlmsg_type = NLMSG_DONE;
  sub_msg.nlh.nlmsg_flags = 0;
  sub_msg.nlh.nlmsg_seq = 0;
  sub_msg.nlh.nlmsg_pid = getpid();

  sub_msg.cn_msg.id.idx = CN_IDX_PROC;
  sub_msg.cn_msg.id.val = CN_VAL_PROC;
  sub_msg.cn_msg.len = sizeof(enum proc_cn_mcast_op);

  sub_msg.op = PROC_CN_MCAST_LISTEN;

  if (send(sock, &sub_msg, sizeof(sub_msg), 0) < 0) {
    perror("send subscription");
    exit(EXIT_FAILURE);
  }

  while (true) {
    ssize_t ret = recv(sock, &msg, sizeof(msg), 0);
    if (ret < 0) {
      perror("recv");
    }
    switch (msg.proc_ev.what) {
    case PROC_EVENT_EXEC:
      printf("Exec event: PID %d\n", msg.proc_ev.event_data.exec.process_pid);
      break;
    case PROC_EVENT_EXIT:
      printf("Exit event: PID %d\n", msg.proc_ev.event_data.exit.process_pid);
    default:
      break;
    }
  }
  return EXIT_SUCCESS;
}
