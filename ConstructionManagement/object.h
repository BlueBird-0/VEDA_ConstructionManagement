#ifndef OBJECT_H
#define OBJECT_H

class Object
{
    int m_id;
public:
    Object();
    Object(int id);
    virtual void showInfo() = 0;
};

#endif // OBJECT_H
