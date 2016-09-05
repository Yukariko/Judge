#ifndef _LANGUAGE_H
#define _LANGUAGE_H

class Language
{
public:

    enum LangId {C, CPP, JAVA};

    static Language* languageFactory(LangId langId)
    {
        switch(langId)
        {
            case C: return new C();
            case CPP: return new Cpp();
            case JAVA: return new Java();
        }

        return nullptr;
    }

    virtual 

private:
};

class C : public Language
{
public:



private:


};

class Cpp : public Language
{

};

class Java : public Language
{

}

#endif