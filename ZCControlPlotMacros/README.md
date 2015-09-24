Processed using ROOT 6.

Set ntuples and other parameters in ZCStandardVariables.h before running.

You will need to change settings in the main running files to switch between Zuu
and Zee mode.

To run control plot maker, compile with:

`g++ -o ZCControlPlotter ZCControlPlotMaker.cpp main_makePlots.cpp \`root-config --cflags --glibs\``

To run:

`./ZCControlPlotter <Z-decay-pref> <dataset> <maxEvents>`

* <Z-decay-pref> - Either _zuu_ or _zee_
* <dataset>      - one of the following: _muon, elec, dy, dy1j, ww, wz, zz, ttlep, ttsemi, tthad_
* <maxEvents>    - If not specfied or negative, runs through full file




Commands to run through code. The first four take a long time, so I usually do
those separately and copy and paste the rest all at once.

```./ZCControlPlotter Zuu muon

./ZCControlPlotter Zee elec

./ZCControlPlotter Zuu dy

./ZCControlPlotter Zee dy

./ZCControlPlotter Zee ww
./ZCControlPlotter Zee wz
./ZCControlPlotter Zee zz
./ZCControlPlotter Zee tthad
./ZCControlPlotter Zee ttlep
./ZCControlPlotter Zee ttsemi
./ZCControlPlotter Zuu ww
./ZCControlPlotter Zuu wz
./ZCControlPlotter Zuu zz
./ZCControlPlotter Zuu tthad
./ZCControlPlotter Zuu ttlep
./ZCControlPlotter Zuu ttsemi
```


To combine the plots, run the main_comboPlots.C macro using root:

`root -l -b main_comboPlots.C`
