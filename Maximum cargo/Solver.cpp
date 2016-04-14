#include "stdafx.h"
#include "Solver.h"

Graph CSolver::ReadGraph(std::ifstream &file)
{
	Graph result;
	m_countRoads = 0;

	int firstTown = 0;
	int secondTown = 0;
	int cargo = 0;
	while (!file.eof())
	{
		if ((m_amountTowns == 0) && (m_amountRoads == 0))
		{
			file >> m_amountTowns;
			file >> m_amountRoads;

			CheckAmountTownsAndRoads();

			std::string passString;
			std::getline(file , passString);

			result.resize(m_amountTowns, std::vector<int>(m_amountTowns, 0));
		}

		file >> firstTown;
		file >> secondTown;
		file >> cargo;
		result[--firstTown][--secondTown] = cargo;

		m_countRoads++;
		CheckRoadCounters();
	}
	CheckRoadCounters();

	return result;
}

std::vector<int> CSolver::GetMaxCargoForOtherTowns(const Graph & graph)
{
	int graphSize = static_cast<int>(graph.size());
	std::vector<int> label(graphSize, std::numeric_limits<int>::min());
	std::vector<bool> isVisited(graphSize, false);

	int indexMaxCargo = std::numeric_limits<int>::min();
	///////
	for (size_t index1 = 0; index1 < graphSize; index1++)// XXX
	{
		///////

		for (size_t index2 = 0; index2 < graphSize; index2++)
		{
			if ((graph[index1][index2] > label[index2]) && !isVisited[index2])
			{
				label[index2] = graph[index1][index2];
				indexMaxCargo = index2;
			}
		}
		isVisited[indexMaxCargo] = true;
		//
		for (size_t index2 = 0; index2 < graphSize; index2++)
		{
			if (!isVisited[index2]
				&& graph[indexMaxCargo][index2]
				&& (label[indexMaxCargo] != std::numeric_limits<int>::min())
				&& ((graph[indexMaxCargo][index2]) >= label[index2]))
			{
				label[index2] = graph[indexMaxCargo][index2];
			}
		}
		///////
	}
	///////
	/*
	#include <iostream>
using namespace std;

const int V=6;

int *Dijkstra(int **GR, int V, int st) {
//�������� �������� - ������� ���������� ������� ����� st
//����� GR ������������ V	�� ���� ���������
//������ ������ ����������, INT_MAX - ������� ���
 int *distance, count, index, i, u;
 bool *visited;
 distance = new int [V];
 visited = new bool [V];
 for (i=0; i<V; i++) { distance[i]=INT_MAX; visited[i]=false; }
 distance[st]=0;

 for (count=0; count<V-1; count++) { 
  int min=INT_MAX;
  for (i=0; i<V; i++)
  if (!visited[i] && distance[i]<=min) { min=distance[i]; index=i; }
  u=index;
  visited[u]=true;
  for (i=0; i<V; i++)--------------
  if (!visited[i] && GR[u][i] && distance[u]!=INT_MAX &&
       distance[u]+GR[u][i]<distance[i])
   distance[i]=distance[u]+GR[u][i];
 }
 return distance;
}

void main() {
 setlocale(LC_ALL, "Rus");
 int start, **GR;
 GR = new int * [V];
 for (int i=0; i<V; i++) GR[i] = new int [V]; //���������������� ������� ��������� GR
  
 int DATA[] = { //0 - ��� �����, ����� ������������� "���" �����
  0, 1, 1, 0, 1, 0,
  0, 0, 0, 1, 0, 0,
  1, 0, 0, 1, 0, 0,
  0, 1, 1, 0, 0, 1,
  0, 0, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 0
 };
 int i,j,k=0;
 for (i=0; i<V; i++)
 for (j=0; j<V; j++) GR[i][j]=DATA[k++];

 start=0; //��������� �������, ��������� � 0

 int *distance=Dijkstra(GR, V, start);

 int m=start+1;
 cout << "��������� ���� �� ��������� ������� �� ���������:\n";
 for (i=0; i<V; i++) 
  if (distance[i]!=INT_MAX)
   cout << m << " > " << i+1 << " = " << distance[i] << endl;
  else cout << m << " > " << i+1 << " = " << "������� ����������" << endl;

 system("pause>>void");
}
	*/

	label.erase(label.begin());

	return label;
}

void CSolver::CheckAmountTownsAndRoads()
{
	if ((m_amountTowns < 1) && (m_amountRoads < 1))
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_SIZE);
	}
}

void CSolver::CheckRoadCounters()
{
	if ((static_cast<int>(m_countRoads) > m_amountRoads))
	{
		//throw std::invalid_argument(MESSAGE_WIDTH_MORE_EXPECTED);
	}
}

SPoint::SPoint()
	: x(0)
	, y(0)
{
}

SPoint::SPoint(size_t first, size_t second)
	: x(first)
	, y(second)
{
}

SRange::SRange()
{
}

SRange::SRange(size_t indexStart, size_t indexEnd)
{
	m_indexStart = indexStart;
	m_indexEnd = indexEnd;
}

