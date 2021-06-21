import subprocess
import sys
import os
import shutil
from PyQt5.QtWidgets import QApplication, QWidget, QFileDialog
from PyQt5 import uic

global path
global file_name
global file_raw
global flag

flag = 0
path = ''


def end():
    sys.exit()


class AudioConverter(QWidget):
    def __init__(self):
        super().__init__()
        uic.loadUi('Audio Converter.ui', self)

        self.Imp.clicked.connect(self.browse)
        self.Conv.clicked.connect(self.convert)
        self.Exit.clicked.connect(end)
        self.Inp.hide()

    def browse(self):
        global flag
        global path
        global file_name
        global file_raw
        flag = 1

        array = QFileDialog.getOpenFileName(self, 'Select Song', '', 'RAW files(*.raw)')
        path = array[0].split('.')
        path = path[0].split('/')

        file_raw = path[-1] + '.raw'
        file_name = path[-1]

        path.pop()
        path = '/'.join(path)

        self.Info.setText('Write the name of .h file')
        self.Inp.show()
        self.Inp.setDisabled(False)

    def convert(self):
        global flag
        global path
        global file_name
        global file_raw
        if (flag == 0) or (path == ''):
            self.Info.setText('Select the song first')
        else:
            original_path = subprocess.run('cd', shell=True, capture_output=True)
            original_path = original_path.stdout.decode()
            shutil.copy('xxd.exe', path)
            file = self.Inp.toPlainText()
            os.chdir(path)
            subprocess.run('xxd -i ' + file_raw + ' ' + file + '.h', shell=True)
            os.remove('xxd.exe')

            with open(file + '.h', 'r') as f:
                f_contents = f.read()
                f_contents = f_contents.split('=')
                no_of_bits = f_contents[-1]
                no_of_bits = no_of_bits[1:-2]

                f_contents.pop()
                edit = f_contents[1]
                edit = edit.split('unsigned')
                f_contents[1] = edit[0]

                first_line = f_contents[0]
                f_contents[0] = first_line[:-3] + '[' + no_of_bits + first_line[-2:] + 'PROGMEM '

                f_contents = '='.join(f_contents)

            with open(file + '.h', 'w') as f:
                f.write(f_contents)

            os.chdir(original_path[:-2])
            flag = 0
            self.Info.setText('Done')
            self.Inp.hide()
            self.Inp.setDisabled(True)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    audio = AudioConverter()
    audio.show()

    try:
        sys.exit(app.exec())
    except SystemExit:
        print('Closing Window...')
