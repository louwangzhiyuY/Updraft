#include "Lifecycle.hpp"

#include "UefiSystem.hpp"
#include "Logger.hpp"

EFI_EVENT Lifecycle::s_timerEvent = nullptr;

EFI_EVENT Lifecycle::s_eventList[];

uintn Lifecycle::s_eventIndex = 0;

uint8 Lifecycle::s_fps = 60;

uint32 Lifecycle::s_frameCount = 0;

void Lifecycle::ResetTimer()
{
  {
    const auto status = UefiSystem::SystemTable()->BootServices->SetTimer(s_timerEvent, ::TimerCancel, 0);
    if(EFI_ERROR(status))
    {
      Logger::Println_("Error: ", PrintEfiStatus(status), " on reset timer.");
      UefiSystem::SleepForever();
    }
  }

  {
    const auto status = UefiSystem::SystemTable()->BootServices->SetTimer(s_timerEvent, ::TimerPeriodic, 10000000 / s_fps);
    if(EFI_ERROR(status))
    {
      Logger::Println_("Error: ", PrintEfiStatus(status), " on reset timer.");
      UefiSystem::SleepForever();
    }
  }
}

void Lifecycle::Initialize()
{
  const auto status = UefiSystem::SystemTable()->BootServices->CreateEvent(EVT_TIMER, 0, nullptr, nullptr, &s_timerEvent);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", PrintEfiStatus(status), " on timer event setup.");
    UefiSystem::SleepForever();
  }

  s_eventList[0] = s_timerEvent;

  ResetTimer();
}

bool Lifecycle::Update()
{
  const auto status = UefiSystem::SystemTable()->BootServices->WaitForEvent(1, s_eventList, &s_eventIndex);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", PrintEfiStatus(status), " on update.");
    UefiSystem::SleepForever();
  }

  s_frameCount++;

  return true;
}

uint8 Lifecycle::FPS()
{
  return s_fps;
}

void Lifecycle::FPS(const uint8 fps)
{
  s_fps = fps;
  ResetTimer();
}

uint32 Lifecycle::FrameCount()
{
  return s_frameCount;
}
