//---------------------------------------------------------------------------

#ifndef SMSH
#define SMSH

#include <Sockets.hpp>
#include "Dialogs.hpp"


//---------------------------------------------------------------------------
//! ����� �� �������� � �������� ��������� ����� ������������ � ������������� �� TCP/IP
class SMS
{
private:
	//! ������ ��� ������ � ��������
	TTcpServer *Server;
	//! ������ ��� ������ � ��������
	TTcpClient *Client;
	//! ������ ���������� ������ ��������
	wchar_t client_rec[50];
	//!	������ ���������� ������ ��������
	wchar_t server_rec[50];
	//!	����� ���������� ������ ��������
	int server_rec_length;
	//! ����� ���������� ������ ��������
	int client_rec_length;
	//! ����� ������� (?) ����� �� ����� �������
	int sen_length;
	//! ������� - ������ ������� ������
	TEvent *client_get;

	//! ��������� ����� ������� �� ���������� �������
	String CreateServerRespond();
	//! �������: ������ �������� ������ ������, ���������� �����
	void __fastcall ServerAccept(TObject *Sender, TCustomIpClient *ClientSocket);
	//! �������: ������ ������
	void __fastcall ServerCreateHandle(TObject *Sender);
	//! �������: ������ ���������
	void __fastcall ServerDestroyHandle(TObject *Sender);
	//!	�������: ������ �������� ������ �� ������
	void __fastcall ServerSend(TObject *Sender, PChar Buf, int &DataLen);
	//!	�������: ������ ������ ������ �� �������
	void __fastcall ServerReceive(TObject *Sender, PChar Buf, int &DataLen);

	//! �������: ������ �������� ������
	void __fastcall ClientSend(TObject *Sender, PChar Buf, int &DataLen);
	//! �������: ������ ������ ������
	void __fastcall ClientReceive(TObject *Sender, PChar Buf, int &DataLen);
	//! �������: ������ ����������� � �������
	void __fastcall ClientConnect(TObject *Sender);
	//! �������: ������ ���������� �� �������
	void __fastcall ClientDisconnect(TObject *Sender);
	//! �������: ������ ��� �������� � �������
	void __fastcall ClientError(TObject *Sender, int SocketError);

	HWND main_handle;
	UINT sms_msg;
	void Post(WPARAM _w, LPARAM _l = 0);
public:
	//! ����������� �� ���������
	SMS(TComponent *Owner,HWND _main_handle, UINT _sms_msg);
	//! ����������
	~SMS();
	//! ������� ��� ������� ��� ��������
	String ServerName;
	//! ����� ����� (������ ���� ���������� � ����� �����������)
	int Port;
	//! ����� ����� � �����
	int length_in_zones;
	//! @brief ������� ������� ������ ���� �� ����
	//! @param sendString ������, ������� ����� ���������
	void SendAnyMessage(String sendString);
	//! @brief ��������� ������ �� ������� � ���������� ����
	//! @param zone ����� ����
	//! @param thickness ����������� ������� � ���� ����
	bool SendZoneThickness(int zone , double thickness);
	//! ��������� ����� ����� � �����
	int AskTubeLength();
	//! ���� ������ ����� TCP/IP
	bool TestConnection();
	//! ���������� ������ ��������
	void StartServer();
	double cur_thick;
};
//---------------------------------------------------------------------------
extern SMS* sms;
//---------------------------------------------------------------------------
#endif
