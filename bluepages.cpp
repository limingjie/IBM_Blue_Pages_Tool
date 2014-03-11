/*-----------------------------------------------------------------------------+
|                                                                              |
|  bluepages.cpp                                                               |
|                                                                              |
|  Description - Bluepages Class                                               |
|  Author      - Li Ming Jie (Martin)                                          |
|  Email       - mingjieli@cn.ibm.com                                          |
|  Created     - 2009.10.28                                                    |
|  Licence     - Free                                                          |
|  Copyright   - Free                                                          |
|                                                                              |
+-----------------------------------------------------------------------------*/

#include "bluepages.h"

bluepages::bluepages()
{
    initial();
}

bluepages::~bluepages()
{
    clear();
}

string bluepages::url(string function, string parameter)
{
    if(function.compare("allByNotesID") == 0)
    {
        parameter = encode_notesid(parameter);
    }

    this->function = function;
    this->parameter = parameter;

    string url =
        "http://bluepages.ibm.com/BpHttpApisv3/wsapi?" +
        function + "=" + parameter;

    return url;
}

string bluepages::result(size_t row, string column_name)
{
    person_t::iterator it;

    it = persons[row]->find(column_name);
    if(it != persons[row]->end())
    {
        return it->second;
    }

    return string("");
}

size_t bluepages::row_count()
{
    return persons.size();
}

size_t bluepages::column_count()
{
    if(persons.size() == 0) return 0;

    return persons[0]->size();
}

void bluepages::clear()
{
    size_t size= persons.size();

    for(size_t i = 0; i < size; i++)
    {
        delete persons[i];
    }

    persons.clear();
}

bool bluepages::split(string &line, string &key, string &value)
{
    size_t pos;

    pos = line.find(':');
    if(pos == string::npos)
    {
        return false;
    }

    key = line.substr(0, pos);
    pos = line.find_first_not_of(": ", pos);
    if(pos == string::npos)
    {
        value = string("");
    }
    else
    {
        value = line.substr(pos);
    }

    return true;
}

size_t bluepages::translate(string &page)
{
    string line, key, value;
    size_t pos = 0, pos_s;
    size_t initial_count = persons.size();

    person = NULL;

    while(pos != string::npos)
    {
        // Get line.
        pos_s = page.find_first_of("\r\n", pos);
        line = page.substr(pos, pos_s - pos);
        pos = page.find_first_not_of("\r\n", pos_s);

        // Process last line of page.
        if(line[0] == '#')
        {
            if(person != NULL) persons.push_back(person);

            break;
        }

        if(split(line, key, value))
        {
            if(person == NULL)
            {
                person = new person_t;
                //person->insert(pair<string, string>("KEYWORD", parameter));
                //person->insert(pair<string, string>("TYPE", function));
                person->insert(pair<string, string>("REPEAT", "N"));
            }

            if(person->find(key) != person->end())
            {
                persons.push_back(person);

                person = new person_t;
                //person->insert(pair<string, string>("KEYWORD", parameter));
                //person->insert(pair<string, string>("TYPE", function));
                person->insert(pair<string, string>("REPEAT", "Y"));
            }

            if(key.compare("NOTESID") == 0) value = decode_notesid(value);
            person->insert(pair<string, string>(key, value));
        }
    }

    return persons.size() - initial_count;
}

string bluepages::decode_notesid(string id)
{
    size_t pos;

    // Find "CN="
    if((pos = id.find("CN=")) != string::npos)
    {
        id.erase(pos, 3);
    }

    // Find "OU="
    // One more loop for "OU=Contr"
    while((pos = id.find("OU=")) != string::npos)
    {
        id.erase(pos, 3);
    }

    // Find "O="
    if((pos = id.find("O=")) != string::npos)
    {
        id.erase(pos, 2);
    }

    return id;
}

string bluepages::encode_notesid(string id)
{
    size_t pos, pos_o;

    // If already has '=', treat it as already encoded.
    if(id.find("=") != string::npos)
    {
        return id;
    }

    id = "CN=" + id;

    pos = id.find("/", 3);
    if(pos != string::npos)
    {
        id.insert(pos + 1, "OU=", 3);

        pos = id.find("/", pos + 4);
        while(pos != string::npos)
        {
            pos_o = id.find("/", pos + 1);
            if(pos_o != string::npos)
            {
                id.insert(pos + 1, "OU=", 3);
            }
            else
            {
                id.insert(pos + 1, "O=", 2);
            }

            pos = id.find("/", pos + 2);
        }
    }

    return id;
}

QString bluepages::autoType(QString value)
{
    if(!value.contains(' '))
    {
        if(value.contains('@'))
        {
            return QString("byInternetAddr");
        }
        else if(value.contains(QRegExp("[0-9]")))
        {
            switch(value.size())
            {
            case 6 :
                return QString("bySerial");
            case 9 :
                return QString("byCnum");
            }

            if(QRegExp("[0-9]+").exactMatch(value) ||
               QRegExp("[a-z][0-9]+").exactMatch(value))
            {
                if(value.size() < 6)
                    return QString("bySerial");
                else if(value.size() < 9)
                    return QString("byCnum");
            }
        }

        return QString("byInternetAddr");
    }

    if(value.contains('/') || value.contains('@') || value.contains('=') )
        return QString("allByNotesID");

    return QString("allByNameFuzzy");
}

void bluepages::initial()
{
    /// BluePages Web Server API
    functions.push_back("auto");
    functions.push_back("byCnum");
    functions.push_back("bySerial");
    functions.push_back("allByName");
//    functions.push_back("allByNameLite");
    functions.push_back("allByNameFuzzy");
//    functions.push_back("allByNameFuzzyLite");
    functions.push_back("allByNotesID");
//    functions.push_back("allByNotesIDLite");
    functions.push_back("byInternetAddr");
    functions.push_back("managerChainFor");
    functions.push_back("directReportsOf");
//    functions.push_back("directReportsOfLite");
//    functions.push_back("membersOfDept");
//    functions.push_back("membersOfDeptLite");
//    functions.push_back("depts");
//    functions.push_back("cCodes");
//    functions.push_back("workLoc");
//    functions.push_back("eCodes");
//    functions.push_back("orgCodes");

    /// BluePages Web Server API Description
    functions_description.push_back("Auto");
    functions_description.push_back("CNUM (S/N+Country Code)");
    functions_description.push_back("S/N");
    functions_description.push_back("Name (e.g. A, B)");
//    functions_description.push_back("allByNameLite");
    functions_description.push_back("Name Fuzzy (e.g. A,B)");
//    functions_description.push_back("allByNameFuzzyLite");
    functions_description.push_back("Notes ID");
//    functions_description.push_back("allByNotesIDLite");
    functions_description.push_back("Internet Address");
    functions_description.push_back("Report Chain (CNUM)");
    functions_description.push_back("Direct Report Of (CNUM)");
//    functions_description.push_back("directReportsOfLite");
//    functions_description.push_back("Department (div+dept)");
//    functions_description.push_back("membersOfDeptLite");
//    functions_description.push_back("depts");
//    functions_description.push_back("cCodes");
//    functions_description.push_back("workLoc");
//    functions_description.push_back("eCodes");
//    functions_description.push_back("orgCodes");

    /// BluePages Web Server API Result Columns
    //columns.push_back("KEYWORD");
    //columns.push_back("TYPE");
    columns.push_back("REPEAT");

    // Lite Columns (20 cols)
    columns.push_back("CNUM");
    columns.push_back("DEPT");
    columns.push_back("DIRECTORY");
    columns.push_back("DIV");
    columns.push_back("EMAILADDRESS");
    columns.push_back("EMPCC");
    columns.push_back("EMPNUM");
    columns.push_back("EMPTYPE");
    columns.push_back("INTERNET");
    columns.push_back("JOBRESPONSIB");
    columns.push_back("MGRCC");
    columns.push_back("MGRNUM");
    columns.push_back("MNUM");
    columns.push_back("NAME");
    columns.push_back("NODE");
    columns.push_back("NOTESID");
    columns.push_back("ORGCODE");
    columns.push_back("PDIF");
    columns.push_back("USERID");
    columns.push_back("XPHONE");

    // Additional Columns (29 cols)
    columns.push_back("ADDITIONAL");
    columns.push_back("BACKCC");
    columns.push_back("BACKNUM");
    columns.push_back("BLDG");
    columns.push_back("C");
    columns.push_back("CELLULAR");
    columns.push_back("COMPANY");
    columns.push_back("COUNTRY");
    columns.push_back("FAX");
    columns.push_back("FAXTIE");
    columns.push_back("FLOOR");
    columns.push_back("IMAD");
    columns.push_back("INFOPHONES");
    columns.push_back("LOCCITY");
    columns.push_back("MGR");
    columns.push_back("MGRNAME");
    columns.push_back("NODEA");
    columns.push_back("OFFICE");
    columns.push_back("PAGER");
    columns.push_back("PAGERID");
    columns.push_back("PAGERTYPE");
    columns.push_back("SECCC");
    columns.push_back("SECNUM");
    columns.push_back("SHIFT");
    columns.push_back("TIEA");
    columns.push_back("USERIDA");
    columns.push_back("WORKLOC");
    columns.push_back("WORKPLACEIND");
    columns.push_back("XPHONEA");

    // ASCA Columns (20 cols)
    columns.push_back("HRACTIVE");
    columns.push_back("HRASSIGNEE");
    columns.push_back("HRASSIGNMENT");
    columns.push_back("HRCOMPANYCODE");
    columns.push_back("HRCOUNTRYCODE");
    columns.push_back("HRDEPARTMENT");
    columns.push_back("HRDIVISION");
    columns.push_back("HREMPLOYEETYPE");
    columns.push_back("HRFAMILYNAME");
    columns.push_back("HRFIRSTNAME");
    columns.push_back("HRINITIAL");
    columns.push_back("HRLASTNAME");
    columns.push_back("HRMANAGERINDICATOR");
    columns.push_back("HRMANAGERPSC");
    columns.push_back("HRMANAGERSERIAL");
    columns.push_back("HRMIDDLENAME");
    columns.push_back("HROTHERNAME");
    columns.push_back("HRPREFERREDNAME");
    columns.push_back("HRPSC");
    columns.push_back("HRSERIALNUMBER");

    columns_lite.push_back("CNUM");
//    columns_lite.push_back("EMPNUM");
//    columns_lite.push_back("EMPCC");
    columns_lite.push_back("NAME");
    columns_lite.push_back("NOTESID");
    columns_lite.push_back("INTERNET");
//    columns_lite.push_back("JOBRESPONSIB");
//    columns_lite.push_back("EMPTYPE");
    columns_lite.push_back("USERID");
    columns_lite.push_back("XPHONE");
    columns_lite.push_back("MNUM");
    columns_lite.push_back("MGRNUM");
    columns_lite.push_back("MGRCC");
    columns_lite.push_back("DIV");
    columns_lite.push_back("DEPT");
    columns_lite.push_back("DIRECTORY");
    columns_lite.push_back("EMAILADDRESS");
    columns_lite.push_back("NODE");
    columns_lite.push_back("ORGCODE");
    columns_lite.push_back("PDIF");
}
