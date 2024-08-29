#ifndef OBJECT_H
#define OBJECT_H

class Object
{
    int m_id;
public:
    Object() : Object(-1) {}
    Object(int id) : m_id(id) {}
    int getId() { return m_id; }
    virtual void showInfo() = 0;
};

#endif // OBJECT_H
