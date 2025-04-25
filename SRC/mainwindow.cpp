#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

extern "C" {
#include <libavformat/avformat.h>
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), textEdit(new QTextEdit(this)) {
    auto *button = new QPushButton("选择视频文件", this);
    auto *widget = new QWidget(this);
    auto *layout = new QVBoxLayout(widget);
    layout->addWidget(button);
    layout->addWidget(textEdit);
    setCentralWidget(widget);

    connect(button, &QPushButton::clicked, this, &MainWindow::openFile);
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "选择视频文件");
    if (fileName.isEmpty()) return;

    AVFormatContext *fmt_ctx = nullptr;
    if (avformat_open_input(&fmt_ctx, fileName.toStdString().c_str(), nullptr, nullptr) != 0) {
        QMessageBox::critical(this, "错误", "无法打开视频文件！");
        return;
    }

    avformat_find_stream_info(fmt_ctx, nullptr);
    QString info;
    info += QString("格式: %1\n").arg(fmt_ctx->iformat->name);
    info += QString("时长: %1 秒\n").arg(fmt_ctx->duration / AV_TIME_BASE);
    info += QString("码率: %1 kbps\n").arg(fmt_ctx->bit_rate / 1000);

    for (unsigned i = 0; i < fmt_ctx->nb_streams; ++i) {
        AVStream *stream = fmt_ctx->streams[i];
        AVCodecParameters *codecpar = stream->codecpar;
        if (codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            info += QString("视频流 #%1: %2x%3\n").arg(i).arg(codecpar->width).arg(codecpar->height);
        }
    }

    textEdit->setPlainText(info);
    avformat_close_input(&fmt_ctx);
}
