Identical File - Qt applications
====================================================
Description
-----------
Developed a multi-threaded analogue of fdupes tool for searching duplicated files in the selected directory

Install Qt 5 on Ubuntu
---------------------
Open a terminal. Type the following command and hit Enter:
```bash
sudo apt-get install qt5-default
```

Run application
----------------------
Open a terminal. Type the following command and hit Enter:
Steps:
```bash
git clone https://github.com/ShSamariddin/identical-file.git
cd identical-file
chmod u+x linux.sh
./linux.sh
```
## Preview
![preview.gif](https://i.loli.net/2020/09/27/MlGn5aDwKX6LHSe.gif)

### Screenshot

##### default state
![Screenshot from 2020-09-27 18-22-22.png](https://i.loli.net/2020/09/27/aY7Vg4GIxl9UtJd.png)
##### descending order
![Screenshot from 2020-09-27 18-48-19.png](https://i.loli.net/2020/09/27/5hkPwrs8Oy1IKXG.png)
##### ascending order
![Screenshot from 2020-09-27 18-48-10.png](https://i.loli.net/2020/09/27/oSFvZmnU3QhtOH7.png)

### Features
* User interface
* Sort files by size
* Use hash sha256 for hashing files to quickly check all pairs for identity
