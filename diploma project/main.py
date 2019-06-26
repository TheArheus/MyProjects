import design_v2, scrap, language_detect
from PyQt5 import sip
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QFileDialog
import sys
import nltk
import re
import os
nltk.data.path.append('nltk_data')

#sys.setrecursionlimit(5000)

regex = re.compile(
        r'^(?:http|ftp)s?://' # http:// or https://
        r'(?:(?:[A-Z0-9](?:[A-Z0-9-]{0,61}[A-Z0-9])?\.)+(?:[A-Z]{2,6}\.?|[A-Z0-9-]{2,}\.?)|' #domain...
        r'localhost|' #localhost...
        r'\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})' # ...or ip
        r'(?::\d+)?' # optional port
        r'(?:/?|[/?]\S+)$', re.IGNORECASE)

class DiplomaApp(QtWidgets.QMainWindow, design_v2.Ui_MainWindow):
    def __init__(self):
        self.url_data = None
        self.filepath = None
        self.sent_count = 7

        super().__init__()
        self.setupUi(self)
        self.summarize_1.clicked.connect(self.web_scrap)
        self.get_path.clicked.connect(self.FileDialog_call)
        self.sumarize_2.clicked.connect(self.document_scrap)
        self.Submit.clicked.connect(self.settings_submit)


    def web_scrap(self):
        url = self.url_full.text()

        if not url:
            error_dialog = QtWidgets.QErrorMessage()
            error_dialog.showMessage('Пожалуйста, напишите или вставьте ссылку на сайт')
            error_dialog.exec_()
            return

        if not re.match(regex, url):
            error_dialog = QtWidgets.QErrorMessage()
            error_dialog.showMessage('Введённая вами ссылка не является URL-адресом или не полная.'
                                     ' Пожалуйста, введите или вставьте полную ссылку на сайт')
            error_dialog.exec_()
            return

        article = scrap.scrap(url)
        if not article:
            error_dialog = QtWidgets.QErrorMessage()
            error_dialog.showMessage('Пожалуйста, проверьте интернет соединение')
            error_dialog.exec_()
            return

        language = language_detect.detect_language(article)
        text, format_text = scrap.format_text(article, language)
        result = scrap.summarize(text, format_text, language, self.sent_count)

        name = QtWidgets.QFileDialog.getSaveFileName(self, "Save File", None,"All Files (*);;Text Files (*.txt)")
        if not name[0]:
            return
        file = open(name[0], 'w')

        res = ""
        for s in result:
            res += "{}\n".format(s)

        file.write(res)
        file.close()

    def document_scrap(self):
        data = None
        path = self.file_path.text()

        if path != self.filepath:
            self.filepath = path

        if not self.filepath:
            error_dialog = QtWidgets.QErrorMessage()
            error_dialog.showMessage('Пожалуйста, вставьте или напишите путь к файлу')
            error_dialog.exec_()
            return

        if not os.path.exists(self.filepath):
            error_dialog = QtWidgets.QErrorMessage()
            error_dialog.showMessage('Введённый путь или не правильный, или не существует.'
                                     'Пожалуйста, вставьте или напишите правильный путь к файлу')
            error_dialog.exec_()
            return

        f = open(self.filepath, 'r')

        with f:
            data = f.read()

        language = language_detect.detect_language(data)

        text, format_text = scrap.format_text(data, language)
        result = scrap.summarize(text, format_text, language, self.sent_count)

        name = QtWidgets.QFileDialog.getSaveFileName(self, "Save File", "", "All Files (*);;Text Files (*.txt)")

        if not name[0]:
            return

        if name[0].endswith((".doc", ".docx")):
            pass

        file = open(name[0], 'w')

        res = ""
        for s in result:
            res += "{}\n".format(s)

        file.write(res)
        file.close()

    def FileDialog_call(self):
        fname = QFileDialog.getOpenFileName(self, 'Open file')[0]

        if not fname:
            return

        self.file_path.setText(fname)
        self.filepath = fname

    def settings_submit(self):
        self.sent_count = int(self.ref_size.text())


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = DiplomaApp()
    window.ref_size.setText(str(window.sent_count))
    window.show()
    app.exec_()


if __name__ == "__main__":
    main()
