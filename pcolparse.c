#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Driver code
int main()
{
  FILE* ptr;
  int ch;
  int upper;
  int lower;
  int b1, b2, b3, b4;
  int source_add[4];
  int destination_add[4];

  ptr = fopen("message1", "r");

  //do {
    ch = (int)(fgetc(ptr));

    // IP header
    // first check Ver and IHL
    int ver;
    int ihl;
    ver = ch >> 4;
    ihl = ch % 32;

    // Service
    int service = (int)(fgetc(ptr));

    // Total length
    upper = (int)(fgetc(ptr)) << 8;
    lower = (int)(fgetc(ptr));
    int total_length = upper + lower;

    // ID
    upper = (int)(fgetc(ptr)) << 8;
    lower = (int)(fgetc(ptr));
    int id = upper + lower;

    // Flag + fragment offset
    upper = (int)(fgetc(ptr));
    lower = (int)(fgetc(ptr));
    int flag = upper >> 5;
    upper |= 00011111;
    upper = upper >> 8;
    int fragment_offset = upper + lower;

    // Time
    int time = (int)(fgetc(ptr));

    // Protocol
    int protocol = (int)(fgetc(ptr));

    // header_checksum
    upper = (int)(fgetc(ptr)) << 8;
    lower = (int)(fgetc(ptr));
    int header_checksum = upper + lower;

    // source_add
    b1 = (int)(fgetc(ptr));
    b2 = (int)(fgetc(ptr));
    b3 = (int)(fgetc(ptr));
    b4 = (int)(fgetc(ptr));
    source_add[0] = b1;
    source_add[1] = b2;
    source_add[2] = b3;
    source_add[3] = b4;
    // TODO: parse this as a string
    // destinatiod
    b1 = (int)(fgetc(ptr));
    b2 = (int)(fgetc(ptr));
    b3 = (int)(fgetc(ptr));
    b4 = (int)(fgetc(ptr));
    destination_add[0] = b1;
    destination_add[1] = b2;
    destination_add[2] = b3;
    destination_add[3] = b4;
    // TODO: parse this as a string


    // TCP

    // source port
    b1 = (int)(fgetc(ptr)) << 8;
    b2 = (int)(fgetc(ptr));
    int source_port = b1 + b2;

    // destination port
    b1 = (int)(fgetc(ptr)) << 8;
    b2 = (int)(fgetc(ptr));
    int destination_port = b1 + b2;

    // seq no.
    b1 = (int)(fgetc(ptr)) << 24;
    b2 = (int)(fgetc(ptr)) << 16;
    b3 = (int)(fgetc(ptr)) << 8;
    b4 = (int)(fgetc(ptr));
    int seq_number = b1 + b2 + b3 + b4;

    // ack no.
    b1 = (int)(fgetc(ptr)) << 24;
    b2 = (int)(fgetc(ptr)) << 16;
    b3 = (int)(fgetc(ptr)) << 8;
    b4 = (int)(fgetc(ptr));
    int ack_number = b1 + b2 + b3 + b4;

    // data_offset
    b1 = (int)(fgetc(ptr));
    b2 = (int)(fgetc(ptr));
    int data_offset = b1 >> 4;
    b1 = b1 % 32;
    b1 = b1 << 4;
    int reserved_and_flags = b1 + b2;

    // window
    b1 = (int)(fgetc(ptr)) << 8;
    b2 = (int)(fgetc(ptr));
    int window = b1 + b2;

    // checksum
     b1 = (int)(fgetc(ptr)) << 8;
    b2 = (int)(fgetc(ptr));
    int check_sum= b1 + b2;


    // urgent pointer
    b1 = (int)(fgetc(ptr)) << 8;
    b2 = (int)(fgetc(ptr));
    int urgent_pointer = b1 + b2;

    // options
    b1 = (int)(fgetc(ptr)) << 16;
    b2 = (int)(fgetc(ptr)) << 8;
    b3 = (int)(fgetc(ptr));
    int options = b1 + b2 + b3;

    // padding
    int padding = (int)(fgetc(ptr));

    // data
    // TODO

  //} while (ch != EOF);

  int packet_no = 1;
  printf("%d.%d.%d.%d %d.%d.%d.%d %d %d %d %d", source_add[0], source_add[1], source_add[2], source_add[3], destination_add[0], destination_add[1], destination_add[2], destination_add[3], ihl, total_length, data_offset, packet_no);
  do {
    ch = (int)(fgetc(ptr));
    b1 = b2;
    b2 = b3;
    b3 = b4;
    b4 = ch;

    if ((b1==source_add[0]) && (b2 == source_add[1]) && (b3 == source_add[2]) && (b4 == source_add[3])){
      packet_no++;
    }
  } while (ch != EOF);
  fclose(ptr);
  printf("\n");
  printf("%d", packet_no);
  return 0;

}
