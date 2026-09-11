should probably allow ```installed``` to take operands. Right now if you want to check for a certain app, you need grep or something.


Stop parsing as soon as -h is found. in any case if -h or --help is found, all we do is print help. this prevents other errors for overwriting the help screen.

Add build scripts for tests
