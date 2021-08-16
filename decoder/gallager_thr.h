/*
 * File:   gallager_thr.h
 * Author: Canales-Martinez, Isaac Andres
 */

#ifndef GALLAGER_THR_H
#define GALLAGER_THR_H

#if defined (G1_01_491_345)
#define update_thr(t, iter, i) \
	{\
		switch ((i)) {\
		case 0:\
			(t) = 8;\
			break;\
		case 1:\
			(t) = 7;\
			break;\
		case 2:\
			(t) = 4;\
			break;\
		default:\
			(t) = ((i) < ((iter) / 2)) ? 2 : 0;\
		}\
	}
#elif defined (G1_01_491_360)
#define update_thr(t, iter, i) \
	{\
		switch ((i)) {\
		case 0:\
			(t) = 8;\
			break;\
		case 1:\
			(t) = 7;\
			break;\
		case 2:\
			(t) = 4;\
			break;\
		default:\
			(t) = ((i) < ((iter) / 2)) ? 1 : 0;\
		}\
	}
#elif defined (G2_02_491_345) || defined (G2_02_491_360)
#define update_thr(t, iter, i) \
	{\
		switch ((i)) {\
		case 0:\
			(t) = 8;\
			break;\
		case 1:\
			(t) = 7;\
			break;\
		case 2:\
			(t) = 5;\
			break;\
		default:\
			(t) = ((i) < ((iter) / 2)) ? 2 : 0;\
		}\
	}
#elif defined (G2_03_491_345) || defined (G2_03_491_360)
#define update_thr(t, iter, i) \
	{\
		switch ((i)) {\
		case 0:\
			(t) = 8;\
			break;\
		case 1:\
			(t) = 7;\
			break;\
		case 2:\
			(t) = 6;\
			break;\
		default:\
			(t) = ((i) < ((iter) / 2)) ? 3 : 0;\
		}\
	}
#elif defined (G2_04_491_345) || defined (G2_04_491_360)
#define update_thr(t, iter, i) \
	{\
		switch ((i)) {\
		case 0:\
			(t) = 8;\
			break;\
		case 1:\
			(t) = 7;\
			break;\
		case 2:\
			(t) = 6;\
			break;\
		case 3:\
			(t) = 4;\
			break;\
		default:\
			(t) = ((i) < ((iter) / 2)) ? 1 : 0;\
		}\
	}
#endif

#endif /* GALLAGER_THR_H */
