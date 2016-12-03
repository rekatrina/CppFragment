#pragma once
#ifndef ROUTENODE_H
#define ROUTENODE_H

#include <string>



class routeNode
{
public:

	routeNode();
	~routeNode();

private:
	int id_;

	double latitude_;
	double longitude_;
	double altitude_;

	float speed_;
	float yawDegree_;

	int holdTime_;
	std::string turnMode_;

public:
	//static std::string* attributeList;
};

//routeNode.attributeList = { "id", "latitude" };

#endif // !ROUTENODE_H
