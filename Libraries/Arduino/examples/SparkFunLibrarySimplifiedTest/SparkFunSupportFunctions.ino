// Support functions.

#define NOTE_DIVISOR 2  // My cheesy way of reducing the note frequencies to a range
                        //  that doesn't cause the motor to slip. I *could* rewrite
                        //  the wantYouGone() function to change the notes, but that
                        //  would be a lot of work.

int stepDir = 1;        // Direction flipping bit. Rather than all going one way,
                        //  they change directions. It looks cooler.

// To play a note, we start the motor spinning at the note's frequency in steps/s.
//  The run() function automagically calculates the appropriate value to feed to the
//  dSPIN part based on the desired steps/s.
void playNote(int note, int duration) {
  if (stepDir == 1)  board.run(FWD, note/NOTE_DIVISOR);
  else               board.run(REV, note/NOTE_DIVISOR);
  delay(duration);
  stepDir*=-1;
  board.softStop();
  while (board.busyCheck());
}

// This is the configuration function for the dSPIN parts. Read the inline
//  comments for more info.
void dSPINConfig(void) {
  board.SPIPortConnect(&SPI);             // Before doing anything else, we need to
                                          //  tell the objects which SPI port to use.
                                          //  Some devices may have more than one.

  board.configSyncPin(BUSY_PIN, 0);       // BUSY pin low during operations;
                                          //  second paramter ignored.
  board.configStepMode(STEP_FS);          // 0 microsteps per step
  board.setMaxSpeed(10000);               // 10000 steps/s max
  board.setFullSpeed(10000);              // microstep below 10000 steps/s
  board.setAcc(10000);                    // accelerate at 10000 steps/s/s
  board.setDec(10000);
  board.setSlewRate(SR_530V_us);          // Upping the edge speed increases torque.
  board.setOCThreshold(OC_750mA);         // OC threshold 750mA
  board.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  board.setOCShutdown(OC_SD_DISABLE);     // don't shutdown on OC
  board.setVoltageComp(VS_COMP_DISABLE);  // don't compensate for motor V
  board.setSwitchMode(SW_USER);           // Switch is not hard stop
  board.setOscMode(INT_16MHZ);            // for boardA, we want 16MHz
                                          //  external osc, 16MHz out. boardB
                                          //  will be the same in all respects
                                          //  but this, as it will generate the
                                          //  clock.
  board.setAccKVAL(128);                  // We'll tinker with these later, if needed.
  board.setDecKVAL(128);
  board.setRunKVAL(128);
  board.setHoldKVAL(32);                  // This controls the holding current; keep it low.
}
