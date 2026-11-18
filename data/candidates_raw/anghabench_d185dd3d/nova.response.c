static bool func0(int port)
{
	bool rc;

	
	if ((port >= 5 && port <= 8) || (port >= 13 && port <= 16))
		rc = true;
	else if ((port >= 9 && port <= 12) || (port >= 21 && port <= 24))
		rc = true;
	else
		rc = false;

	return rc;
}