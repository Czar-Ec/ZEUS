#pragma once
#include "imgui.h"
#include "IconsFontAwesome4.h"

/**
* helpMarker
* function that makes a little popup that contains the text passed to it when
* the user scrolls over the question mark that activates the function
*
* @param const char *desc
*/
void helpMarker(const char * desc)
{
	ImGui::TextDisabled(ICON_FA_QUESTION_CIRCLE);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

/**
* UIButton
* similar function to helpMarker
* however this is for situatios where the question mark icon isn't needed
*
* @param const char *buttonIcon
* @param const char *desc
*/
void tooltip(const char *desc)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}