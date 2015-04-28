#include "Nodo.h"

Nodo::Nodo( Shell shell_, Nodo *sig_)
{
	shell = shell_;
	sig = sig_;
}

Nodo::~Nodo()
{
}

Shell Nodo::getShell()
{
	return shell;
}