#include <stdio.h>
#include <stdlib.h> // for malloc(), free()
#include <string.h>

#include "word_extractor.h"
#include "word_tally.h"
#include "LLNode.h"

/**
 * A tool to hold the words we care about in an array, and
 * provide a method for processing the file.
 *
 */

// forward declarations
static int updateWordInTallyList(LLNode **wordLists, int maxLen, char *word);

/*
 * Here we do all the work, processing the
 * file and determining what to do for each word as we
 * read it.  Once we are done reading, we can then
 * examine our wordsToCheck list and see what their
 * state is
 */
int tallyWordsInFile(char *filename, LLNode **wordLists, int maxLen)
{
	struct WordExtractor *wordExtractor = NULL;
	char *aWord = NULL;
	// add any more variables that you need


	// create the extractor and open the file
	wordExtractor = weCreateExtractor(filename, maxLen);

	if (wordExtractor == NULL) {
		fprintf(stderr, "Failed creating extractor for '%s'\n", filename);
		return 0;
	}

	/** TODO: ensure that all of the word list heads are NULL */

	for (int i = 0; i < maxLen; i++)
	{
		wordLists[i] = NULL;
	}



	// read each word from the file using the WordExtractor,
	// and for each tally how often it has been used in
	// the appropriate list

	// In the loop, figure out whether we have seen this
	// word before, and do the appropriate thing if we have

	int totalWordCount = 0;

	while (weHasMoreWords(wordExtractor)) {
		aWord = weGetNextWord(wordExtractor);
		totalWordCount++;

		// figure out whether we have seen this word before,
		// and do the appropriate thing if we have
		updateWordInTallyList(wordLists, maxLen, aWord);
	}

	// is there anything else you need to do at the end of the loop?
	printf("Total word count %d\n", totalWordCount);

	// Close the file when we are done
	weDeleteExtractor(wordExtractor);

	return 1;
}

/**
 * TODO: Either update the tally in the list, or add it to the list
 */
static int
updateWordInTallyList(LLNode **wordListHeads, int maxLen, char *word)
{
     // variables
	 int tester = strlen(word); // length of the word string stored
	 LLNode *existing = wordListHeads[tester];
     

      // checking if the length is less then the max
	  if (tester > maxLen)
	  {
		fprintf(stderr, "invalid word length of '%s' \n ", word);
	 
	    return 0;
	  }
 
    // looking up word by traversing linked list
	 while(existing!= NULL)
	 {
		if(strcmp(existing->key, word) == 0)
		{
			existing->value++; // if the word is found then the value variable is incremented for the tally
			return 1;
		}
		existing = existing->next; // if word is not found we move to the next linked list
	 }


    
	 
	char *newCopy = (char * ) malloc((tester + 1) * sizeof(char)); // allocating memory to store a copy of the word string

      // checking for allocation failure
	  if(newCopy == NULL)
	  {
		 fprintf(stderr, "Sorry memory allocation failed");
		 return -1;
	  }

	  strcpy(newCopy,word);
      
	  LLNode *newNode = llNewNode(newCopy,1); // creating a new linked list node

	  wordListHeads[tester] = llPrepend(wordListHeads[tester], newNode); // prepending the new word to the front of the list

	return 1;
}

