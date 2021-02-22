#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <fstream>
#include "HeterogeneousTree.h"\

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCommandLineParser parser;

    parser.addOption(QCommandLineOption({"i", "input"}, "input file", "input", "input.json"));
    parser.addOption(QCommandLineOption({"o", "output"}, "output file", "output", "output.json"));

    parser.process(a);

    QString input_path = parser.value("i");
    QString output_path = parser.value("o");

    std::string buff;
    std::ifstream input(input_path.toLocal8Bit().constData());

    if (input.is_open())
    {
        std::getline(input, buff);
        input.close();
    }
    else
    {
        qDebug() << "file opening error";
    }

    std::shared_ptr<HeterogeneousTree> tree = HeterogeneousTree::FromJson(QString::fromLocal8Bit(buff.c_str()));

    std::ofstream output;
    output.open(output_path.toLocal8Bit().constData());

    if (output.is_open())
    {
        qDebug() << tree->ToJson();

        output << tree->ToJson().toLocal8Bit().constData();
        output.close();
        qDebug() << '\n' << QString("The %1 file is saved").arg(output_path);
    }
    else
    {
        qDebug() << "file opening error";
    }

    return a.exec();
}
