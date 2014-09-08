Solaris10-ditroff
=================

This is the ditroff version of OpenSolaris revision 0 (which should be identical to the latest closed source revision of Solaris 10).
It is part of the code base from which the Heirloom doctools had been created.

Only parts from OpenSolaris rev. 0 are included in this repository.
So there is no `pic`, `grap`, `mpictures` or `mcolor`.
The missing preprocessors and macro packages can be taken from DWB.
Components from Heirloom doctools or Plan9 may also work.
It is likely that groff components are not compatible with this ditroff version since they use advanced language features (e.g. long identifier names).

The repository can be downloaded with the "Download ZIP" button or with the git command
```bash
git clone https://github.com/n-t-roff/Solaris10-ditroff
```
The source code is compiled with `make` and installed with `make install`.
During the build process generated files are removed with `make clean`.
A local git repository is kept up-to-date with `git pull`.

Please report issues to the [issue list](https://github.com/n-t-roff/Solaris10-ditroff/issues).
