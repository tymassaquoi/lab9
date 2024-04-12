#include <stdio.h>
#include <stdlib.h>

#define hashSize 23
// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

struct Node
{
	struct RecordType data;
	struct Node*next;
};

// Fill out this structure
struct HashType
{
struct Node*head;

};

// Compute the hash function
int hash(int x)
{
return x % hashSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}


void insert(struct HashType hashtable[], struct RecordType data)
{
int index=hash(data.id);
struct Node*newNode=(struct Node*)malloc(sizeof(struct Node));
if(newNode==NULL)
{
printf("Memory allocated failed\n");
exit(-1);
}
newNode->data=data;
newNode->next=NULL;

if(hashtable[index].head==NULL)
{
	hashtable[index].head=newNode;
}
else
{
	struct Node*curr=hashtable[index].head;
	while(curr->next!=NULL)
	{
		curr=curr->next;
	}
	curr->next=newNode;
}
}


// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		if(pHashArray[i].head==NULL)
		continue;
		// if index is occupied with any records, print all
		printf("Index %d ->", i);
		struct Node*curr=pHashArray[i].head;
		while(curr!=NULL)
		{
			printf(" %d %c %d ->", curr->data.id, curr->data.name, curr->data.order);
			curr=curr->next;
		}
		printf("\n");
		//printf("NULL\n");
	}
}


int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType hashtable[hashSize]={0};
	
	for(int i=0; i<recordSz;i++)
	{
		insert(hashtable, pRecords[i]);

	}
	displayRecordsInHash(hashtable, hashSize);

	return 0;
}