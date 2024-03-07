
#include "MemoryManager.h"

#include <iomanip>
#include <iostream>
using namespace std;

namespace MemoryManager
{
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT 
	//
	// This is the only static memory that you may use, no other global variables may be
	// created, if you need to save data make it fit in MM_pool
	//
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT


	const int MM_POOL_SIZE = 65536;
	char MM_pool[MM_POOL_SIZE];

	// I have provided this tool for your use
	void memView(int start, int end)
	{

		const unsigned int SHIFT = 8;
		const unsigned int MASK = 1 << SHIFT - 1;

		unsigned int value;	// used to facilitate bit shifting and masking

		cout << endl; // start on a new line
		cout << "               Pool                     Unsignd  Unsigned " << endl;
		cout << "Mem Add        indx   bits   chr ASCII#  short      int    " << endl;
		cout << "-------------- ---- -------- --- ------ ------- ------------" << endl;

		for (int i = start; i <= end; i++)
		{
			cout << (long*)(MM_pool + i) << ':';	// the actual address in hexadecimal
			cout << '[' << setw(2) << i << ']';				// the index into MM_pool

			value = MM_pool[i];
			cout << " ";
			for (int j = 1; j <= SHIFT; j++)		// the bit sequence for this byte (8 bits)
			{
				cout << ((value & MASK) ? '1' : '0');
				value <<= 1;
			}
			cout << " ";

			if (MM_pool[i] < 32)   // non-printable character so print a blank
				cout << '|' << ' ' << "| (";
			else                    // characger is printable so print it
				cout << '|' << *(char*)(MM_pool + i) << "| (";		// the ASCII character of the 8 bits (1 byte)

			cout << setw(4) << ((int)(*((unsigned char*)(MM_pool + i)))) << ")";	// the ASCII number of the character

			cout << " (" << setw(5) << (*(unsigned short*)(MM_pool + i)) << ")";	// the unsigned short value of 16 bits (2 bytes)
			cout << " (" << setw(10) << (*(unsigned int*)(MM_pool + i)) << ")";	// the unsigned int value of 32 bits (4 bytes)

																				//  cout << (*(unsigned int*)(MM_pool+i)) << "|";	// the unsigned int value of 32 bits (4 bytes)

			cout << endl;
		}
	}

	// Initialize set up any data needed to manage the memory pool
	void initializeMemoryManager(void)
	{

		int freeHead = 0; // starting index of the freelist
		int inUseHead = 2; // starting index of the inUselist
		int usedHead = 4; // starting index for the used list - deallocated memory

		int nextLink = 2; // offset index of the next link
		int prevLink = 4; // offset index for the prev link

		*(unsigned short*)(MM_pool + freeHead) = 6; // freelist starts at byte 6
		*(unsigned short*)(MM_pool + inUseHead) = 0;	// nothing in the inUse list yet
		*(unsigned short*)(MM_pool + usedHead) = 0; // nothing in the used list yet

	}
	void* allocate(int aSize)
	{
		if ((int)(*(unsigned short*)(MM_pool)) + aSize + 6 > 65536)
			onOutOfMemory();

		int newNode, inUseHead, newNode_next;
		/*node creation*/
		newNode = *(unsigned short*)&MM_pool[0]; //start of free memory becomes newNode head
		*(unsigned short*)(MM_pool + newNode) = aSize; //insert size
		
		//insert next 
		inUseHead = *(unsigned short*)(MM_pool + 2);
		newNode_next = inUseHead; //old inUse head becomes next 
		*(unsigned short*)(MM_pool + newNode + 2) = newNode_next;

		//head prev links to new node
		if (inUseHead != 0){
			*(unsigned short*)&MM_pool[inUseHead + 4] = newNode;
		}

		//update memory
		*(unsigned short*)&MM_pool[0] += 6 + aSize; //update free memory head
		*(unsigned short*)&MM_pool[2] = newNode; //update inUse head
		//return address to index of user data 
		return (unsigned short*)&MM_pool[newNode + 6];
	}
	// Free up a chunk previously allocated
	void deallocate(void* aPointer)
	{
		int inUseHead = *(unsigned short*)&MM_pool[2];
		int usedHead = *(unsigned short*)&MM_pool[4];
		int delNode, delNode_next, delNode_prev;
		/* retrieve and init node to be deleted from in use*/
		unsigned short* ptr= (unsigned short*)aPointer; 
		//locate index in MMpool by next from ptr arithmetic
		delNode_next = *(ptr - 2); //goes to second offset 
		if (delNode_next == 0){
			//if zero, that means its the tail in the list or first 
			//added adter free memory at index 6
			delNode = 6;
		}
		else {

			//otherwise, locate node index in next node prev
			delNode=*(unsigned short*)&MM_pool[delNode_next + 4];
		}
		delNode_prev = *(unsigned short*)&MM_pool[delNode + 4];

		/* Delete from inUse DLL*/
		/* Base case */
		if (delNode == 0 || inUseHead == 0)
			return;
		/* If deleted node is head*/
		if (inUseHead == delNode)
			MM_pool[inUseHead] = MM_pool[delNode + 2]; //head = delNode->next
		/*If node to be deleted is not last node */
		if (delNode_next != 0){
			//del->next->prev = del->prev
			*(unsigned short*)&MM_pool[delNode_next + 4] = *(unsigned short*)&MM_pool[delNode + 4];
		}
		if (delNode_prev != 0){
			//del->prev->next=del->next
			*(unsigned short*)&MM_pool[delNode_prev + 2] = *(unsigned short*)&MM_pool[delNode + 2];
		}

		/* Used Memory Insert */
		*(unsigned short*)&MM_pool[delNode + 4] = 0; 
		*(unsigned short*)&MM_pool[delNode + 2] = usedHead; // next
		if (usedHead != 0){
			*(unsigned short*)&MM_pool[usedHead + 4] = delNode;
		}
		//update memory
		*(unsigned short*)&MM_pool[4] = delNode;
	}
	int size(void* ptr)
	{
		unsigned short* sizeptr = (unsigned short*)ptr;
		int size = *(sizeptr - 3);

		return size;
	}

	//---
	//--- support routines
	//--- 

	// Will scan the memory pool and return the total free space remaining
	int freeMemory(void)
	{
		//free memory = total - inUse - used
		int x = usedMemory();
		int y = inUseMemory();
		return (MM_POOL_SIZE - x - y - 6);
	}


	// Will scan the memory pool and return the total used memory - memory that has been deallocated
	int usedMemory(void)
	{
		int total = 0;
		int cur = *(unsigned short*)&MM_pool[4];
		int size = *(unsigned short*)&MM_pool[cur];
		int next = *(unsigned short*)&MM_pool[cur + 2];

		while (cur != 0)
		{
			total = total + size + 6;
			cur = next;
			size = *(unsigned short*)&MM_pool[cur]; //keep adding to size
			next = *(unsigned short*)&MM_pool[cur + 2];
		}
		return total;

		return size;
	}

	// Will scan the memory pool and return the total in use memory - memory being curretnly used
	int inUseMemory(void)
	{
		int total = 0;
		int cur = *(unsigned short*)&MM_pool[2];
		int size = *(unsigned short*)&MM_pool[cur];
		int next = *(unsigned short*)&MM_pool[cur + 2];

		while (cur != 0)
		{
			total = total + size + 6;
			cur = next;
			size = *(unsigned short*)&MM_pool[cur]; //keep adding to size
			next = *(unsigned short*)&MM_pool[cur + 2];
		}
		return total;
	}

	// helper function to see teh InUse list in memory
	void traverseInUse()
	{
		int cur = *(unsigned short*)&MM_pool[2];
		int size = *(unsigned short*)&MM_pool[cur];
		int next = *(unsigned short*)&MM_pool[cur + 2];
		int prev = *(unsigned short*)&MM_pool[cur + 4];
		cout << "\nTraversing InUse Memory....";
		cout << "\n      InUse Head:" << cur;
		while (cur != 0)
		{
			cout << "\n        Index:" << cur << " Size:" << size << " Next:" << next << " Prev:" << prev;
			cur = next;
			size = *(unsigned short*)&MM_pool[cur];
			next = *(unsigned short*)&MM_pool[cur + 2];
			prev = *(unsigned short*)&MM_pool[cur + 4];
		}
	}

	//Helper function to seet eh Used list in memory
	void traverseUsed()
	{
		int cur = *(unsigned short*)&MM_pool[4];
		int size = *(unsigned short*)&MM_pool[cur];
		int next = *(unsigned short*)&MM_pool[cur + 2];
		int prev = *(unsigned short*)&MM_pool[cur + 4];
		cout << "\nTraversing Used Memory....";
		cout << "\n      Used Head:" << cur;
		while (cur != 0)
		{
			cout << "\n        Index:" << cur << " Size:" << size << " Next:" << next << " Prev:" << prev;
			cur = next;
			size = *(unsigned short*)&MM_pool[cur];
			next = *(unsigned short*)&MM_pool[cur + 2];
			prev = *(unsigned short*)&MM_pool[cur + 4];
		}

	}

	// this is called from Allocate if there is no more memory availalbe
	void onOutOfMemory(void)
	{
		std::cout << "\nMemory pool out of memory\n" << std::endl;
		std::cout << "\n---Press \"Enter\" key to end program---:";

		cin.get();

		exit(1);
	}
}