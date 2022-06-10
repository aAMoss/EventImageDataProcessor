# Event Image Data Processor
<br>    
## Overview   
The purpose of this program is to pre-process the N-MNIST dataset (an event-image dataset, AER) for classification with a
Multiclass Tsetlin Machine.

The program is still a work in progress, and was created for my 3rd year university project.

Please be nice, this is my first attempt at coding a larger program.

There's a lot to improve and debug, I make no guarantees for the program compiling or working on your system.
<br>
## EIDP
*Coming soon*
<br>  
## TMDA
*Coming soon*
<br>  
# Instructions  
Clone the respository.

Ensure that you have a copy of the N-MNIST dataset in the top-level directory. 

The dataset and its accompanying paper are available [here](https://www.garrickorchard.com/datasets/n-mnist) and [here](https://www.frontiersin.org/articles/10.3389/fnins.2015.00437/full).


Ensure the dataset is located here: EventImageDataProcessor/N-MNIST/

Ensure that its sub-directories are labelled: Test and Train.
<br>
# To Do List 
These are to listed in no particular order.
<br>
##EIDP
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


