#ifndef SERIAL_PORT_H_
#define SERIAL_PORT_H_

#include <string>

namespace serial_Node {
  class serial_Node {
    private:  
      serial_Node()   //构造函数是私有的  
      {  
      }  
      static serial_Node *m_serial_Node;  

    public:
      //virtual ~serial_Node();
      static serial_Node * GetInstance()  
      {  
        if(m_serial_Node == NULL)  //判断是否第一次调用  
            m_serial_Node = new serial_Node(); 
        return m_serial_Node;  
      }
      void initSerial();
      bool openSerial();
      void readline(std::string &buffer);
      void write(const std::string &data);
    }
}

#endif