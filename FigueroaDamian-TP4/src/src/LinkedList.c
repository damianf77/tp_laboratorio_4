#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = (LinkedList*) malloc(sizeof(LinkedList));
    if (this != NULL)
    {
        this ->size = 0;
        this -> pFirstNode = NULL;
    }
    return this;
}

int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL)
    {
        returnAux = this ->size;
    }
    return returnAux;
}

/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* nodo = NULL; //por si algo es invalido

    if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
    {
        nodo = this->pFirstNode; //si me piden el 0 queda ahi.

        for(int i = 0; i < nodeIndex; i++) //si no es 0 entra aca.
        {
            nodo = nodo->pNextNode;
        }
    }
    return nodo;
}

Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* nodo;
    Node* nodoAnterior;

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
        nodo = (Node*) malloc(sizeof(Node));

        if(nodo != NULL)
        {
            nodo->pElement = pElement;

            if(nodeIndex == 0)
            {
                nodo->pNextNode = this->pFirstNode;
                this->pFirstNode = nodo;
            }
            else
            {
                nodoAnterior = getNode(this, nodeIndex-1);
                nodo->pNextNode = nodoAnterior->pNextNode;
                nodoAnterior->pNextNode = nodo;
            }
            this->size++;
            returnAux = 0;
        }
    }
    return returnAux;
}

int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}

int ll_add(LinkedList* this, void* pElement)
{
    return addNode(this,ll_len(this),pElement);
}

void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;

    Node* auxNodo;
    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        auxNodo = getNode(this,index);
        if(auxNodo != NULL)
        {
            returnAux = auxNodo->pElement;
        }
    }

    return returnAux;
}

int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;

    Node* auxNodo;
    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        auxNodo = getNode(this,index);
        if(auxNodo != NULL);
        {
            //No hace faltar hacer free porque otro lo puede estar usando.
            auxNodo->pElement = pElement;
            returnAux = 0;
        }
    }
    return returnAux;
}

int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* auxNode;
    Node* nodoAnterior;
    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        auxNode = getNode(this,index);
        if(auxNode != NULL)
        {
            if(index == 0)
            {
                this->pFirstNode = auxNode->pNextNode;
                this->size--;
                free(auxNode);
                returnAux = 0;

            }
            else
            {
                nodoAnterior = getNode(this,index-1);
                if(nodoAnterior != NULL)
                {
                    nodoAnterior->pNextNode = auxNode->pNextNode;
                    this->size--;
                    free(auxNode);
                    returnAux = 0;

                }
            }
        }
    }
    return returnAux;
}

int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        int longitudLista = ll_len(this);

        for(int i = longitudLista; i >= 0; i--)
        {
            ll_remove(this,i);
        }
        returnAux = 0;
    }
    /*
    while(ll_len(this))
    {
    ll_remove(this,0);
    returnAux = 0;
    }
    */

    return returnAux;
}

int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        if(ll_clear(this)==0)
        {
            free(this);
            returnAux = 0;
        }
    }
    return returnAux;
}

int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
        int longitudLista = ll_len(this);

        for(int i = 0; i < longitudLista; i++)
        {
            if(ll_get(this,i)== pElement)
            {
                returnAux = i;
                break;
            }
        }
    }
    return returnAux;
}

int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(this->pFirstNode == NULL)
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

int ll_push(LinkedList* this, int index, void* pElement)
{
    return addNode(this,index,pElement);
}

void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        returnAux = ll_get(this,index);
        ll_remove(this,index);
    }
    return returnAux;
}

int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
        if(ll_indexOf(this,pElement)!=-1)
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }

    }
    return returnAux;
}

int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    void* auxiliarElemento;

    if(this != NULL && this2 != NULL)
    {
        returnAux = 0;
        int longitudLista2 = ll_len(this2);
        for(int i = 0; i < longitudLista2; i++)
        {
            auxiliarElemento = ll_get(this2,i);

            if(ll_contains(this,auxiliarElemento)==0)
            {
                returnAux = 0;
                break;
            }
            else
            {
                returnAux = 1;
            }
        }
    }

    return returnAux;
}

LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    void* elementoAux;

    int longitud = ll_len(this);
    if(this != NULL && from >= 0 && from < longitud && to >= from && to <= longitud)
    {
        cloneArray = ll_newLinkedList();
        if(cloneArray != NULL)
        {
            for(int i = from; i < to; i++)
            {
                elementoAux = ll_get(this,i);
                ll_add(cloneArray,elementoAux);
            }
        }

    }
    return cloneArray;
}

LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    cloneArray = ll_subList(this,0,ll_len(this));
    return cloneArray;
}

int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    void* elementoAux;
    void* elementoAux2;
    int longitudLista;
    if(this != NULL && pFunc != NULL && (order==0 || order ==1))
    {
        longitudLista = ll_len(this);
        for(int i = 0; i < longitudLista - 1; i++)
        {
            for(int j = i + 1; j < longitudLista; j++)
            {
                elementoAux = ll_get(this,i);
                elementoAux2 = ll_get(this,j);
                if((pFunc(elementoAux,elementoAux2)>0 && order==1) || (pFunc(elementoAux,elementoAux2)<0 && order==0))
                {
                    ll_set(this,i,elementoAux2);
                    ll_set(this,j,elementoAux);
                }
            }
        }
        returnAux = 0;
    }
    return returnAux;

}

//filter llama a pFunc y le pasa cada uno de los elementos de la lista y si pFunc devuelve 1(TRUE) a ese elemento lo agrego a lanueva lista
//devuelve un nuevo linkedlist
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*))
{
    LinkedList* listaFiltrada = NULL;
    void* auxElement = NULL;

    if(this != NULL && pFunc != NULL)
    {
        listaFiltrada = ll_newLinkedList();
        if(listaFiltrada !=NULL)
        {
            for (int i = 0; i< ll_len(this); i++)
            {
                auxElement =ll_get(this, i);
                if (pFunc(auxElement) )
                {
                    ll_add(listaFiltrada, auxElement);
                }

            }
        }

    }
    return listaFiltrada;
}

int ll_count(LinkedList* this, int (*pFunc)(void* element))
{
    void* auxElement = NULL;
    int contador = 0;
    if(this != NULL && pFunc != NULL)
    {
        for (int i = 0; i< ll_len(this); i++)
        {
            auxElement =ll_get(this, i);
            contador = contador + pFunc(auxElement);
        }

    }
    return contador;
}