#include <stdio.h>
#include <unistd.h>

#define GPIO67_DIR "../../sys/class/gpio/gpio67/direction"
#define GPIO68_DIR "../../sys/class/gpio/gpio68/direction"
#define GPIO44_DIR "../../sys/class/gpio/gpio44/direction"

#define GPIO67_VAL "../../sys/class/gpio/gpio67/value"
#define GPIO68_VAL "../../sys/class/gpio/gpio68/value"
#define GPIO44_VAL "../../sys/class/gpio/gpio44/value"

#define BUZZER_PPATH "../../sys/devices/ocp.3/pwm_test_P9_14.15/period"
#define BUZZER_DPATH "../../sys/devices/ocp.3/pwm_test_P9_14.15/duty"

void toggleLED(char * path, char * flag);
void toggleIO(char * path);
void setPeriod(int ns);

int main() {
  while (1) {
    toggleIO(GPIO67_DIR);
    toggleIO(GPIO68_DIR);
    toggleIO(GPIO44_DIR);

    toggleLED(GPIO67_VAL, "0");
    toggleLED(GPIO68_VAL, "0");
    toggleLED(GPIO44_VAL, "0");

    for (int i = 0; i < 8; i++) {
      int cur = i;
      if (cur % 2 == 1) {
	toggleLED(GPIO44_VAL, "1");
      } else {
	toggleLED(GPIO44_VAL, "0");
      }
      cur /= 2;
      if (cur % 2 == 1) {
	toggleLED(GPIO68_VAL, "1");
      } else {
	toggleLED(GPIO68_VAL, "0");
      }
      cur /= 2;
      if (cur % 2 == 1) {
	toggleLED(GPIO67_VAL, "1");
      } else {
	toggleLED(GPIO67_VAL, "0");
      }
      setPeriod(1300000 + i * 200000);
      sleep(1);      
    }
  }
}

void toggleLED(char * path, char * flag) {
  FILE *f =  fopen(path, "w");
  fprintf(f, flag);
  fclose(f);
}

void toggleIO(char * path) {
  FILE *f =  fopen(path, "w");
  fprintf(f, "out");
  fclose(f);
}

void setPeriod(int ns) {
  FILE *f = fopen(BUZZER_PPATH, "w");
  fprintf(f,"%d", ns);
  fclose(f);

  f = fopen(BUZZER_DPATH, "w");
  fprintf(f, "%d", ns / 2);
  fclose(f);
}
