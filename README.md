# Event Image Data Processor

## Overview   
The purpose of this program is to pre-process the N-MNIST dataset (an event-image dataset, AER) for classification with a
Multiclass Tsetlin Machine.

The program is still a work in progress, and was created for my 3rd year university project.

Please be nice, this is my first attempt at coding a larger program.

There's a lot to improve and debug, I make no guarantees for the program compiling or working on your system.

I currently run a Manjaro-based OS, in the past I have run the program on both MacOS and WIndows with a few alterations, in
future I will be making the necessary additions to ensure it can run on each of these platforms without issue.

<br>

### EIDP
*Coming soon*
<br>  

### TMDA
*Coming soon*
<br>  



# Instructions  

## Set-up
Clone the respository.

Ensure that you have a copy of the N-MNIST dataset in the top-level directory. 

The dataset and its accompanying paper are available [here](https://www.garrickorchard.com/datasets/n-mnist) and [here](https://www.frontiersin.org/articles/10.3389/fnins.2015.00437/full).

Ensure the dataset is located here: EventImageDataProcessor/N-MNIST/

Ensure that its sub-directories are labelled: Test and Train.

Run make to generate the two tools: eidp and tmda.

*WIP*
<br> 

## To Run

To run the program:

./eidp $MODE   $FEATURES   $SIZE   $OVERLAP

###$MODE: 	

The feature extraction method, choose: 

raw	-	no processing of any kind, extracts the event data and converts to a boolean representation without any processing, feature extraction, 
		or minimization.
pbfe - 	a statistical patch-based feature extraction method, will be linking the relevant paper.
idfe - 	an inter-packet feature extraction method, will be linking the relvant paper that inspired it.


###$FEATURES: 

The number of features. Determines the number of booleans for each data sample when generating the dataset for the Tsetlin Machine.

Depending on the feature extraction method this may be overidden or prompt the user to select a different value.

###$SIZE:

Sets the number of events in each event packet. Default range is 100 to 1500 events, these limits can be altered prior to compiling the program. 

###$OVERLAP:

Sets the number of events by which the event packets overlap. The range is 0 to $SIZE-1. This ensures that the overlap is always less than the packet size.
<br> 




# To Do List 

## EIDP

- [ ] Improve that shambles of a makefile
- [ ] Create hyper.c and hyper.h, all hyper parameters for the pipeline will be stored and modified from here
- [ ] Commandline arguments, will require moving a lot of code from eidp.c into another source file
- [ ] Improve and expand on data logging functions, will all be moved to (and called from) log.c log.h
- [ ] Improve terminal messages when program is in operation, possible another source file
- [ ] Improve and refactor pbfe.c, need to decide whether to keep its write-to-file functions or move to dataio.c
- [ ] Improve and refactor idfe.c, need to decide whether to keep its write-to-file functions or move to dataio.c 
- [ ] Improve and refactor... or nix completely... raw.c and raw.h
- [ ] Add multi-threading, one way to increase the program's execution speed.
<br>

## TMDA

- [ ] Major refactor and improvement, this is vague I know
- [ ] More logging, better logging
- [ ] Multi-threading, it's fairly fast already but why not.
- [ ] Better terminal messages
- [ ] Commandline arguments, omg it's tedious to copy and paste the directory name you wish to process, I know I said no particular order but...
<br>

