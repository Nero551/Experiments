using System;
using Godot;

public static class TestService
{
    public static bool HasRequiredBlocks(Entity entity)
    {
        return true;
    }

    public static void StartEntities(Entity entity)
    {
        if (!HasRequiredBlocks(entity))
            return;
    }
}
