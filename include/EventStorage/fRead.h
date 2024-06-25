/**
 \brief EventStorage library, an abstract interface for file I/O operations
 \author Szymon Gadomski
 \file EventStorage/fRead.h
 \date Feb 2006 - Feb 2007

 This is needed to support dufferent file I/O libraries:
 - castor files are accessible with shift library,
 - plain disk files need to be readable on computers without the shift lib,
 - dCache is an alternative to Castor used at various sites for ATLAS.
*/

#ifndef FREAD_H
#define FREAD_H

#include <string>
#include <stdint.h>

class fRead 
{
 public:
  fRead()
  {
  	m_currentEndOfFile = -1;
  	//ERS_DEBUG(2," I AM BASECLASS being called");
  };
 
  virtual ~fRead() {}; 

	uint32_t readuint32_t()
	{
		int64_t op = getPosition();
		uint32_t myint;
		readData((char*)&myint, sizeof(uint32_t));
		setPosition(op);
		return myint;
	}

  virtual bool isOpen() = 0;
  virtual bool isEoF() = 0;
  virtual bool fileExists(std::string name) const = 0;
  virtual void openFile(std::string name) = 0;
  virtual void closeFile() = 0;
  virtual void readData(char *buffer, unsigned int sizeBytes) = 0;
  virtual int64_t getPosition() = 0;
  virtual void setPosition(int64_t p) = 0;
  virtual void setPositionFromEnd(int64_t p) = 0;
  
  void setCurrentEndOfFile(int64_t p)
  {
  	m_currentEndOfFile = p;
  }
  
  void setPositionFromEndSafe(int64_t p)
  {
  	if (m_currentEndOfFile==-1) setPositionFromEnd(p);
  	else
  	  	setPosition( m_currentEndOfFile + p);
  }

  virtual fRead * newReader() const = 0;

 private:
 	int64_t m_currentEndOfFile;

};

extern "C" {
  fRead *fReadFactory();
}
#endif 

