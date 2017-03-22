# turul
Tree-Using Really Unorthodox Language: The modern meta-programming system

Description
===========

This repository holds the code and text for my MSc thesis in which I am writing a whole programming environment supporting extensible meta-programming by providing a minimal yet scriptable compilation system (hopefully) with an editor.

The system core for bootstrapping is written in C++, but further language elements will be provided in turul itself.

The goal is a general system that can compile any context-free grammar providing handy ways to expand syntax and semantics while staying as minimal and simple as possible using "suckless.org philosophy" through the code!

Repository structure
====================

docs/   - contains documentation and (Hungarian) text of my thesis in markdown format and various export formats.
core/   - contains a LightWeightComponents pattern based system (will elaborate later)
