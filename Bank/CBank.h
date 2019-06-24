// ---------------------------------------------------------------------------
#ifndef CBankH
#define CBankH
#include <SyncObjs.hpp>
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------
class CBank
{
private:
	TCriticalSection* cs;
	//����.������.���������
public:
	vector<vector<vector<double> > >Source;
public:
	unsigned int zones;
private:
	unsigned int sensors;
public:
	unsigned int last;

public:
	CBank(int _max_zones, int _sensors);
	~CBank(void);
	void Clear(void);
	// ������.���������
	void AddZone(vector<vector<double> >* new_data);
	//����.������.���������
	int GetNextZone(vector<vector<vector<double> > > * _source);
};
#endif
