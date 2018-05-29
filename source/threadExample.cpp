#include<CommonConfig.h>

//***********************�߳���������**********************************//
class ThreadInputData {
public:
	int m_threadId;	//�߳�ID
	
};

//***********************�߳���***************************************//
#ifdef _WIN32
	CRITICAL_SECTION g_hLock;//�����ٽ���ȫ�ֱ���
	#define	 INITLOCK	 InitializeCriticalSection(&g_hLock) //��ʼ���ٽ���  
	#define	 UNINITLOCK	 DeleteCriticalSection(&g_hLock)//ɾ���ٽ���  
	#define	 LOCK		 EnterCriticalSection(&g_hLock)
	#define	 UNLOCK		 LeaveCriticalSection(&g_hLock)
	#define	 MHANDLE		HANDLE
#else
	pthread_mutex_t g_hLock;
	#define	 INITLOCK	 pthread_mutex_init(&g_hLock, NULL)
	#define	 UNINITLOCK  pthread_mutex_destroy(&g_hLock)
	#define	 LOCK		 pthread_mutex_lock(&g_hLock)  //�����ٽ���  
	#define	 UNLOCK		 pthread_mutex_unlock(&g_hLock) //�뿪�ٽ��� 
	#define	 MHANDLE		pthread_t
#endif

//***********************�̺߳���*************************************//
#ifdef _WIN32						 
	DWORD WINAPI ThreadProcess(LPVOID lpParam)
#else
	void* ThreadProcess(void* lpParam)
#endif
	{
		ThreadInputData* threadData = (ThreadInputData*)lpParam;

		/**********************************************************/
		/*���̴߳�����*/
		printf("Thread Test!!!\n");

		LOCK;
		//*���������߳�����*//
		UNLOCK;

		/**********************************************************/
		
		printf("Thread [%d] returned successfully\n", threadData->m_threadId);
		return 0;
	}

int StartMultiThread(int threadNum) {

#ifdef _WIN32
	DWORD ThreadID;
#endif
	MHANDLE* hThread = new MHANDLE[threadNum];
	INITLOCK;

	for (int i = 0; i < threadNum; i++) {
		ThreadInputData* threadInput = new ThreadInputData();
		threadInput->m_threadId = i;
		//�����߳� 
#ifdef _WIN32
		hThread[i] = CreateThread(NULL, 0, ThreadProcess, (LPVOID)(threadInput), 0, &ThreadID);
		printf("Thread #%d has been created successfully.\n", i);
#else
		int pthreadResult = pthread_create(&hThread[i], NULL, ThreadProcess, (void*)threadInput);
		if (pthreadResult == 0) {
			printf("Thread #%d has been created successfully.\n", i);
		}
#endif
		
	}
	//�ȴ����н��̽���  
#ifdef _WIN32
	WaitForMultipleObjects(threadNum, hThread, TRUE, INFINITE);
#else
	pthread_exit(NULL);
#endif
	UNINITLOCK;
	delete []hThread;
	return 0;
}

int main(int argc,char** argv) {

	StartMultiThread(5);
	return 0;
}


