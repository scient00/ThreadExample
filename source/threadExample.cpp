#include<CommonConfig.h>

//***********************线程输入数据**********************************//
class ThreadInputData {
public:
	int m_threadId;	//线程ID
	
};

//***********************线程锁***************************************//
#ifdef _WIN32
	CRITICAL_SECTION g_hLock;//定义临界区全局变量
	#define	 INITLOCK	 InitializeCriticalSection(&g_hLock) //初始化临界区  
	#define	 UNINITLOCK	 DeleteCriticalSection(&g_hLock)//删除临界区  
	#define	 LOCK		 EnterCriticalSection(&g_hLock)
	#define	 UNLOCK		 LeaveCriticalSection(&g_hLock)
	#define	 MHANDLE		HANDLE
#else
	pthread_mutex_t g_hLock;
	#define	 INITLOCK	 pthread_mutex_init(&g_hLock, NULL)
	#define	 UNINITLOCK  pthread_mutex_destroy(&g_hLock)
	#define	 LOCK		 pthread_mutex_lock(&g_hLock)  //进入临界区  
	#define	 UNLOCK		 pthread_mutex_unlock(&g_hLock) //离开临界区 
	#define	 MHANDLE		pthread_t
#endif

//***********************线程函数*************************************//
#ifdef _WIN32						 
	DWORD WINAPI ThreadProcess(LPVOID lpParam)
#else
	void* ThreadProcess(void* lpParam)
#endif
	{
		ThreadInputData* threadData = (ThreadInputData*)lpParam;

		/**********************************************************/
		/*多线程处理函数*/
		printf("Thread Test!!!\n");

		LOCK;
		//*操作公共线程数据*//
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
		//创建线程 
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
	//等待所有进程结束  
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


