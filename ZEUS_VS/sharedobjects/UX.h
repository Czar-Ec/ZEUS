#pragma once
#include "imgui.h"

/**
* helpMarker
* function that makes a little popup that contains the text passed to it when
* the user scrolls over the question mark that activates the function
*
* @param const char *desc
*/
void helpMarker(const char * desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}