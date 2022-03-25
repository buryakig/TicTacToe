#pragma once

#include <memory>
#include <stack>
#include "State.h"

namespace Blink
{
	typedef std::unique_ptr<State> StateUptr;

	class StateMachine
	{
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateUptr newState, bool isReplacing = true);
		void RemoveState();

		void ProcessStateChanges();

		StateUptr& GetActiveState();
	private:
		std::stack<StateUptr> states;
		StateUptr newState;				// Latest state to add

		bool isRemoving;
		bool isAdding;
		bool isReplacing;
	};
}