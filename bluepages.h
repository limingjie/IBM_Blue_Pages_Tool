/*-----------------------------------------------------------------------------+
|                                                                              |
|  bluepages.h                                                                 |
|                                                                              |
|  Description - Bluepages Class                                               |
|  Author      - Li Ming Jie (Martin)                                          |
|  Email       - mingjieli@cn.ibm.com                                          |
|  Created     - 2009.10.28                                                    |
|  Licence     - Free                                                          |
|  Copyright   - Free                                                          |
|  Version     -                                                               |
|  Changes     -                                                               |
|    2009.10.28 Created                                                        |
|    2010.07.01 Upgrade for bluepages WSAPI V3                                 |
|                                                                              |
+-----------------------------------------------------------------------------*/

#ifndef __BLUEPAGES_H__
#define __BLUEPAGES_H__

#include <QString>
#include <QRegExp>

#include <iostream>

#include <map>
#include <string>
#include <vector>

using namespace std;

typedef map<string, string> person_t;
typedef vector<person_t *> persons_t;

class bluepages
{
public:

    bluepages();
    ~bluepages();

    string url(string function, string parameter);
    string result(size_t row, string column_name);
    size_t row_count();
    size_t column_count();
    size_t translate(string &page);
    void   clear();
    QString autoType(QString value);

    vector<string> functions;
    vector<string> functions_description;
    vector<string> columns;
    vector<string> columns_lite;

private:

    persons_t persons;
    person_t *person;

    string function;
    string parameter;

    void   initial();
    bool   split(string &line, string &key, string &value);
    string decode_notesid(string id);
    string encode_notesid(string id);
};

#endif
