cd src
qmake identical-file.pro
make
./identical-file
rm *.o
rm moc_*
rm ui_*
rm identical-file
rm .qmake.stash
rm Makefile
#xdg-open .

