/*
Name: Muhammad Kashif
Date: 16 January, 2013
File: mkArray.h (side class)
Desc: Fast dynamic array

Status:  completed
Reviewd: 19 Jan, 2013
	   : 09 Apr, 2013

Pointer Error Removed
*/

#ifndef MK_ARRAY_H
#define MK_ARRAY_H
#pragma once


template <class DATA_TYPE>
class mkArray
{
private:
	int count;
	DATA_TYPE *data;
public:
	mkArray(){
		count = 0;
		data = NULL;
	}
	mkArray(int count)
	{
		this->count = count;
		this->data = new DATA_TYPE[this->count];
	}
	mkArray(DATA_TYPE *data, int count)
	{
		this->count = count;
		
		this->data = new DATA_TYPE[count];
		DATA_TYPE *ptr = this->data;
		DATA_TYPE *p = data;
		memcpy(ptr,p,count*sizeof(DATA_TYPE));
	}
	
	void PushData(DATA_TYPE *data, int count)
	{
		if(this->data!=NULL)
		{
			DATA_TYPE* ptr = this->data;
			DATA_TYPE* tempData = new DATA_TYPE[this->count];
			
			// copying this->data to tempData
			memcpy(tempData,ptr,this->count*sizeof(DATA_TYPE));
			delete []this->data;

			// creating new large array
			this->data = new DATA_TYPE[this->count+count];
			memcpy(this->data,tempData,this->count*sizeof(DATA_TYPE));
			
			// appending new data
			ptr  = this->data+this->count;
			memcpy(ptr,data,count*sizeof(DATA_TYPE));

			this->count += count;
		}
		else
		{
			this->count = count; 
			this->data = new DATA_TYPE[this->count];
			memcpy(this->data,data,this->count*sizeof(DATA_TYPE));
		}
	}
	void ReplaceData(DATA_TYPE *data, int count)
	{
		this->count = count;

		// deleting old data
		delete[] this->data;

		this->data = new DATA_TYPE[this->count];
		memcpy(this->data,data,sizeof(DATA_TYPE)*count);

	}
	
	DATA_TYPE *operator[](int index)
	{
		if(index<this->count && index>-1)
			return &this->data[index];
		else
		{
			cout <<"Index Out of Bound..!!";
		}
	}
	
	
	DATA_TYPE *get()
	{
		return this->data;
	}
	int getCount()
	{
		return count;
	}
	Uint32 getSizeInBytes()
	{
		return (Uint32)sizeof(DATA_TYPE)*count;
	}
	float getSizeInKB()
	{
		return (float)getSizeInBytes()/1024;
	}
	float getSizeInMB()
	{
		return (float)getSizeInKB()/1024;
	}

	void DisplayData()
	{
		for(int i=0; i<this->count; i++){
			cout <<this->data[i]<<" ";
		}
	}
	void Delete()
	{
		delete[] data;
	}

};
#endif