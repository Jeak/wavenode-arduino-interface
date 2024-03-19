// Interface code to read power values from Wavenode HF-1/UHF-1 sensor

int fwdPin = A0; // analog pin 0 connected to pin 3 (FWD) of 6-pin mini din
int revPin = A1; // analog pin 1 connected to pin 5 (REV) of 6-pin mini din

int raw_adc_fwd,raw_adc_rev; // variables to store the raw 10-bit adc values

float v_fwd,v_rev,pwr_fwd,pwr_rev,vswr,gamma; // variables for voltage and power (W) values

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // start uart at 9600 baud

  
}

void loop() {
  // put your main code here, to run repeatedly:

    // Get value from ADC
    raw_adc_fwd = analogRead(fwdPin);
    raw_adc_rev = analogRead(revPin);

    // convert ADC to voltage
    v_fwd = (5.0 * raw_adc_fwd) / 1024;
    v_rev = (5.0 * raw_adc_rev) / 1024;

    // Convert ADC to voltage
    // based on cal table https://wavenodedevelop.com/wp-content/uploads/2017/12/power_cal_3.pdf

    pwr_fwd = (0.00107+ (-0.00822 * v_fwd) + (12.5 * pow(v_fwd,2)));
    pwr_rev = (0.00107+ (-0.00822 * v_rev) + (12.5 * pow(v_rev,2)));

    // calculate VSWR
    gamma = pwr_rev/pwr_fwd;
    vswr = (1+gamma)/(1-gamma);

    // output to serial terminal
    Serial.print("FWD: ");
    Serial.print(pwr_fwd);
    Serial.print(" W\r\n");
    Serial.print("REV: ");
    Serial.print(pwr_rev);
    Serial.print(" W\r\n");

    Serial.print("FWD voltage: ");
    Serial.print(v_fwd);
    Serial.print(" V\r\n");
    Serial.print("REV voltage: ");
    Serial.print(v_rev);
    Serial.print(" V\r\n");

    Serial.print("FWD voltage: ");
    Serial.print(v_fwd);
    Serial.print(" V\r\n");
    Serial.print("REV voltage: ");
    Serial.print(v_rev);
    Serial.print(" V\r\n");

    Serial.print("SWR: ");
    Serial.print(vswr);
    Serial.print("\r\n");

    delay(2000);
}
