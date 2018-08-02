# Programming the Board

To program the board you will need the following:

    ```
        * 2x 3x1 Pin Male Headers (found in Kit with Badge)
        * Header Jumper (Found in Kit with Badge)
        * FTDI dongle (BYOB or we might have a few available at DefCon)
        * Soldering Iron
        * Solder
        * Code
        * About 5 minutes
    ```

Steps:

    1. Solder One of the 3x1 Male Headers to the Programming Interface on the Board Labeled "Jack in Here" pins GND RX and TX
    2. Solder the other 3x1 on the board in location J1 pins GND & io0
    3. Place the Jumper on the PIN to short the above pins GND & io0
    4. Connect in to the Jack in Here Pins

**Note** - Notice there is no VCC On the Jack In Here, so you will need the Batteries installed and Badge on to program (we did this to prevent someone from applying to 5v vs 3v from the FTDI .. dont ask .. it happened)

**Note 2** - Once programmed remove the Jumper from GND and io0 (Convenience that we put that 3rd PIN here so you can just put it between io0 and Extra PIN so you don't lose it, your welcome)

# Attaching Daughter Board

You have 2 choices here. As it sits with the AAA Battery holder on the back you will not be able to attach the Daughter board to the back of the badge, So you will need to attach to the front. No worries, it comes off and I am sure you are going to make someone awesome that you want to show everyone. OR you can replace the AAA Batteries with a LiPo because, well to be honest, you will need the power anyways. Either way ....


You will need the Following:

```
        * 4x 5x1 Female Headers, and male Headers (found in Kit with Badge)
        * 1x 4x1 Female Headers, and male Header (found in Kit with Badge)
        * Soldering Iron
        * Solder
        * About 5 minutes
```

Now comes the easy part. Solder the Headers on. Make sure to put them all on the side you want, Front or Back.
Repeat with Daughter board but with Male Headers.
Boom you are done

# Replace Battery with LiPo

Ok .. I have to admit, If you are going to hack your badge, you will NEED to do this. We designed the badge to Blink. Most people are going to wear it and be at awe with the blinking. But you .. you are different, you are not satisfied with just blinking, I mean come on, this thing has Wifi AND Blue tooth. We get it, but those 2 AAA batteries are just not up to the task. So lets replace them with something more .. well more better.

As always you have more than 1 option .. i will describe 2. The Easy way and the Easier way.

    1. The Easy way - We gave you a daughter board, why not use it.
        1. Remove the AAA Battery holder
        2. Complete the steps to install the Daughter Board Headers
        3. Find you 2 Female Single Pole Headers and attach them to the Holes the Battery holder disconnected from.
        4. Line up the Daughter Board with the 2 since Pole Female headers and Place male headers that line up on the daughter Board
        5. Wire you LiPo into said Male headers
        6. Attach LiPo Charger for extra Credit.
        7. Hot Glue the crap out of everything
        8. Enjoy the near infinite power you badge now how
        9. Start hacking stuff onto it and make it cool

    2. The Easier way
        1. Yeah yeah .. remove AAA Battery Holder
        2. Complete steps for Daughter board
        3. Connect LiPo to the back, don't use Daughter Board
        4. Add LiPo Charger for Extra Credit
        5. Hot Glue or tape the crap out of everything
        6. Enjoy and start hacking

LiPo's and LiPo Chargers you say? LiPo you are on your own, but find me at DefCon I might have a few LiPo charger boards left.
