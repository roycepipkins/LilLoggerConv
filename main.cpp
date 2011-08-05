/*
    Copyright 2011 Royce Pipkins
    royce.pipkins@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtCore/QCoreApplication>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <iostream>
#include <QStringList>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (a.arguments().length() < 2)
    {
        cerr << "Please specify a file name to convert.";
        return (-1);
    }

    QFile* infile = new QFile(a.arguments().at(1));

    if (!infile->exists())
    {
        delete infile;
        infile = new QFile(QDir::currentPath() + "/" + a.arguments().at(1) );
        if (!infile->exists())
        {
            cerr << "Unable to find " << a.arguments().at(1).toStdString();
            return (-2);
        }
    }

    if (!infile->open(QIODevice::ReadOnly))
    {
        cerr << "Unable to open " << infile->fileName().toStdString();
        return(-3);
    }

    QFile* outfile = new QFile(infile->fileName() + ".conv");
    outfile->open(QIODevice::ReadWrite | QIODevice::Truncate);

    if (!outfile->isWritable())
    {
        cerr << "Unable to write to " << outfile->fileName().toStdString();
        return(-4);
    }

    QTextStream in(infile);


    QTextStream out(outfile);
    out.setIntegerBase(10);


    in.skipWhiteSpace();
    char r;
    in >> r;

    out << "x\ty\tz" << endl;

    while(!in.atEnd())
    {
        bool ok;
        QString x , y, z;
        in >> x >> y >> z;

        if (x.size() && y.size() && z.size())
        {
            out << x.toUInt(&ok, 16) << "\t";
            out << y.toUInt(&ok, 16) << "\t";
            out << z.toUInt(&ok, 16) << endl;
        }
    }

    out.flush();
    outfile->close();

    return 0;
}
