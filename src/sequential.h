// sequential.h

#ifndef __SEQUENTIAL_H__
#define __SEQUENTIAL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define NBR_SEQUENTIAL_PAGES 5

#define NBR_STEPS 128
#define NBR_TRANSITIONS 256
#define NBR_SWITCHS_MAX 10
#define NBR_SEQ_COMMENTS 50

/* size of the page */
#define SEQ_PAGE_WIDTH 32 /*16*/
#define SEQ_PAGE_HEIGHT 32 /*16*/

/* elements in the sequential pages */
#define ELE_SEQ_STEP 1
#define ELE_SEQ_TRANSITION 2
#define ELE_SEQ_COMMENT 3

/* used only for edit */
#define EDIT_SEQ_INIT_STEP 20
#define EDIT_SEQ_STEP_AND_TRANS 21
#define EDIT_SEQ_START_MANY_STEPS 22
#define EDIT_SEQ_END_MANY_STEPS 23
#define EDIT_SEQ_START_MANY_TRANS 24
#define EDIT_SEQ_END_MANY_TRANS 25
#define EDIT_SEQ_LINK 26

/* size in pixels (default) */
#define SEQ_SIZE_DEF 48 /*32*/

#define SEQ_COMMENT_LGT 51

typedef struct StrStep
{
	/* step is activated at init */
	char InitStep;
	/* step number */
	int StepNumber;
	/* positions on the page and on which page */
	signed char NumPage; /* -1 if do not exist */
	char PosiX;
	char PosiY;

	/* dynamic state */
	char Activated;
	int TimeActivated;
	
	/* for drawing cross step */
	char OffDrawCrossStep;
	char OffDrawCrossStepOffsetY;
}StrStep;

typedef struct StrTransition
{
	/* condition for the transition to become activated */
	/* if boolean variable true */
	int VarTypeCondi;
	int VarNumCondi;
	/* ! theses numbers are offset in array, NOT the step number displayed for user ! */
	/* number of the steps to activate if condition true
	   >1 if start of 'AND' */
	short int NumStepToActiv[ NBR_SWITCHS_MAX ];
	/* number of the steps to desactivate if condition true
	   >1 if end of 'AND' */
	short int NumStepToDesactiv[ NBR_SWITCHS_MAX ];
	/* if start of 'OR' */
	short int NumTransLinkedForStart[ NBR_SWITCHS_MAX ];
	/* if end of 'OR' */
	short int NumTransLinkedForEnd[ NBR_SWITCHS_MAX ];
	/* Positions on the page and on which page */
	signed char NumPage; /* -1 if do not exist */
	char PosiX;
	char PosiY;

	/* dynamic state */
	char Activated;
}StrTransition;

/*typedef struct StrReturn
{
	short int NumStepToGo;
}StrReturn;
*/

typedef struct StrSeqComment
{
	/* positions on the page and on which page */
	signed char NumPage; /* -1 if do not exist */
	char PosiX;
	char PosiY;
	/* comment string */
	char Comment[ SEQ_COMMENT_LGT ];
}StrSeqComment;


typedef struct StrSequential
{
	StrStep Step[ NBR_STEPS ];
	StrTransition Transition[ NBR_TRANSITIONS ];
	StrSeqComment SeqComment[ NBR_SEQ_COMMENTS ];
	//added in v0.9.100
	char PageComment[NBR_SEQUENTIAL_PAGES][LGT_COMMENT];
}StrSequential;

#ifdef __cplusplus
}
#endif

#endif