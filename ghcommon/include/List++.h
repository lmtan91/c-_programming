
#ifndef _JH_LIST_H_
#define _JH_LIST_H_

#include "gh_types.h"
#include <stdio.h>
#include <unistd.h>

class List
{
public:
	List() { mHead.mNext = &mTail; mTail.mPrev = &mHead; }
	virtual ~List() {}

	class Node
	{
	public:
		Node() : mNext( NULL ), mPrev( NULL ) {} 
		virtual ~Node() {}
	
		Node *next() 
		{ 
			if ( mNext->mNext != NULL )
				return mNext;
			else
				return NULL;
		}
		
		Node *prev()
		{ 
			if ( mPrev->mPrev != NULL )
				return mPrev;
			else
				return NULL;
		}
	
		void insertAfter( Node *node )
		{ 
			node->mNext = mNext;
			node->mPrev = this;
			mNext->mPrev = node;
			mNext = node;
		}
		void insertBefore( Node *node )
		{ 
			node->mNext = this;
			node->mPrev = mPrev;
			mPrev->mNext = node;
			mPrev = node;
		}
		
		void remove()
		{
			mNext->mPrev = mPrev;
			mPrev->mNext = mNext;
		}
		
	private:
		Node *mNext;
		Node *mPrev;
		
		friend class List;
	};
		
	void push_back( Node *node ) { mTail.insertBefore( node ); }
	void push_front( Node *node ) { mHead.insertAfter( node ); }
	
	List::Node *getHead()
	{ 
		if ( mHead.mNext != &mTail ) 
			return mHead.mNext; 
		else 
			return NULL;
	}
	
	List::Node *getTail()
	{ 
		if ( mTail.mPrev != &mHead ) 
			return mTail.mPrev; 
		else 
			return NULL;
	}
	
	int	size()
	{
		int size = 0;
		Node *node = getHead();
		
		while( node )
		{
			node = node->next();
			size++;
		}
		
		return size;
	}
	
	bool empty()
	{
		if ( getHead() == NULL )
			return true;
		else
			return false;
	}
	
	void clear()
	{
		Node *node = getHead();

		while( node )
		{
			Node *tmp = node;
			node = node->next();
			delete tmp;
		}

		mHead.mNext = &mTail; mTail.mPrev = &mHead;
	}

	template<class NodeClass>
	static NodeClass *next( NodeClass *cnode )
	{
		List::Node *node = cnode->next();
		return static_cast<NodeClass*>( node );
	}

	template<class NodeClass>
	static NodeClass *prev( NodeClass *cnode )
	{
		List::Node *node = cnode->prev();
		return static_cast<NodeClass*>( node );
	}
	
	template<class NodeClass>
	static NodeClass *find( List &l, NodeClass &match )
	{
		List::Node *node = l.getHead();
		return find( l, match, static_cast<NodeClass*>( node ) );
	}
	
	template<class NodeClass>
	static NodeClass *find( List &l, NodeClass &match, NodeClass *start )
	{
		List::Node *node = start;
	
		while ( node != NULL )
		{
			NodeClass *c = static_cast<NodeClass*>( node );
			
			if ( *c == match )
				return c;
			
			node = node->next();
		}
			
		return NULL;
	}

private:
	Node mHead;
	Node mTail;
};

template<class NodeClass>
class TypedList
{
public:
	void push_back( NodeClass *node ) { mList.push_back( node ); }
	void push_front( NodeClass *node ) { mList.push_front( node ); }
	
	NodeClass *getHead() 
	{
		return static_cast<NodeClass*>( mList.getHead() );
	}

	NodeClass *getTail() 
	{
		return static_cast<NodeClass*>( mList.getTail() );
	}
	
	int	size() { return mList.size(); }	
	bool empty() { return mList.empty(); }
	void clear() { mList.clear(); }
	
	NodeClass *next( NodeClass *cnode )
	{
		return static_cast<NodeClass*>( cnode->next() );
	}

	NodeClass *prev( NodeClass *cnode )
	{
		return static_cast<NodeClass*>( cnode->prev() );
	}

	NodeClass *find( NodeClass &match )
	{
		return find( match, getHead() );
	}
	
	NodeClass *find( NodeClass &match, NodeClass *start )
	{
		List::Node *node = start;
	
		while ( node != NULL )
		{
			NodeClass *c = static_cast<NodeClass*>( node );
			
			if ( *c == match )
				return c;
			
			node = node->next();
		}
			
		return NULL;
	}
	
	bool remove( NodeClass &match )
	{
		NodeClass *node = find(match);
		if (node)
		{
			node->remove();
			delete node;			
			return true;
		}
		return false;
	}

	template<class ftor>
	void foreach( ftor &func )
	{
		NodeClass *node = getHead();
	
		while ( node != NULL )
		{
			NodeClass *c = node;
			node = next( node );
			
			func( c );			
		}
	}
	

private:
	List	mList;
};

#endif // _JH_EVENTQUEUE_H_
