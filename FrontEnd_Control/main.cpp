#include "mbed.h"
#include "i2c.h"
#include "string.h"

#define SLAVE_ADDR 0xA0
#define BUFFER_SIZE 6



I2C master(I2C_SDA, I2C_SCL);

static const char *to_send[] = {"abcde", "12345", "EFGHI"};

int main() {
  char buf[BUFFER_SIZE];
  int send_index = 0;

  while (1) {
    strcpy(buf, to_send[send_index]);

    // Write the new message to the slave
    if (master.write(SLAVE_ADDR, buf, BUFFER_SIZE)) {
      printf("Failed to write to slave!\n");
    } else {
      printf("Written to slave: %s\n", buf);
    }

    // Read what the slave has (should be identical)
    if (master.read(SLAVE_ADDR, buf, BUFFER_SIZE)) {
      printf("Failed to read from slave!\n");
    } else {
      printf("Read from slave: %s\n", buf);
    }

    // Change the message we're writing to the slave
    send_index++;
    if (send_index > 2) {
      send_index = 0;
    }

    wait_us(500000); // Wait 0.5s
  }
}
