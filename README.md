# Docker Coding Environment (Shamelessly Stolen from Tormlers TheNerdClub)

### About
This is a simple build environment based on Docker and Makefiles for
different kind of programming languages. The basic setup (so currently basically all)
was developed by Roman Keller and shamelessly stolen by me, hihi. The fundamental idea
of this repo is to allow quick and dirty coding for different programming languages like
- c++,
- rust, and
- hopefully more soon.

without poluting your local host operating system with dependencies you just need for some test
implementations. For that purpose, the whole build process is executed within docker and wrapped
via Makefiles to be triggered via commandline on your local host.

### Prerequisites
Basically all you need to use this coding environment is docker and some very basic knownledge of Makefiles.

### How to Use
- Just go (in your terminal) into one of the template projects `./projects/ZZZ_template/cpp_templ` or `./projects/ZZZ_template/rust_templ`
- and run the `make` command.

### How to Create Your Own Projects
- Copy one of the existing template projects,
- update the Dockerfile (if neccessary),
- and update the Makefile according to your source code, and
- run the `make` command.

