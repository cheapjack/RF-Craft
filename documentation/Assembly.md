# Building your own

You can contact [@cheapjack](https://twitter.com/cheapjack) and buy a complete board or you can download this repo, get your PCB's made with someone like [Dirty PCBS](http://dirtypcbs.com/) and assemble your own.

You *could* try to solder complonents onto the board by hand but if you're making more than one it could take a long time. Instead get access to a DIY reflow oven with an [Arduino Re-Flow Oven controller shield](http://www.rocketscream.com/blog/docs-item/reflow-controller-shield/) with [code](https://github.com/rocketscream/Reflow-Oven-Controller), a laser cutter some HF 212 Solder Paste, Mylar Sheet and use a DIY pick and place machine and assemble your PCB components on board.  
Felix Rusu from [Low Power Labs](http://lowpowerlab.com/moteino/#misc) has some great tutorials on this [here](https://www.youtube.com/watch?v=YhavXauuWqY).

# KiCad

## Gerber to Laser Solder Mask

**Assumes use of KiCad or similar schematic editor**


Open Gerber for `F.Mask.gbr` in gerber view
 * `Print` and select:
  * Accurate scale
  * Print to file (pdf)

Open pdf in InkScape
 * Convert to outlines and centre on the right
 * Colour for engraving (green)

Export `.dxf` (and `.eps`)

Engrave Mylar sheet
 * Engrave at Speed 250 / Power 25 (0.1) (bi-dir on)

## Reflow oven

Refer to the [DoES Liverpool](https://github.com/DoESLiverpool) [Reflow Oven Page](https://github.com/DoESLiverpool/wiki/wiki/Reflow-Oven)
i
Select the RoHS-DP - Lead free solder profile

