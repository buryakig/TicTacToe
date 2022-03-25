#include "StateMachine.h"

namespace Blink
{
	void StateMachine::AddState(StateUptr newState, bool isReplacing)
	{
		this->isAdding = true;
		this->isReplacing = isReplacing;

		this->newState = std::move(newState);
	}

	void StateMachine::RemoveState()
	{
		this->isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		if (this->isRemoving && !this->states.empty())
		{
			this->states.pop();

			if (!this->states.empty())
			{
				this->states.top()->Resume();
			}

			this->isRemoving = false;
		}

		if (this->isAdding)
		{
			if (!this->states.empty())
			{
				if (this->isReplacing)
				{
					this->states.pop();
				}
				else
				{
					this->states.top()->Pause();
				}
			}
			this->states.push(std::move(newState));
			this->states.top()->Init();
			this->isAdding = false;
		}
	}

	StateUptr& StateMachine::GetActiveState()
	{
		return this->states.top();
	}
}
