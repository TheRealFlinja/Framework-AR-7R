[EntityEditorProps(category: "Framework7R/Entities/GameMode", description: "SCR_Gamemode7R Component for Resource Handling")]
class S7R_ResourceHandlerComponentClass: ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
/*

This component handles all types of resource/entity generation and validation


TO DO:

	Check if other spawners add to a List of spawned groups and copy functionality

*/

class S7R_ResourceHandlerComponent: ScriptComponent
{
	//------------------------------------------------------------------------------------------------
	// Public functions
	Resource GenerateAndValidateResource(string resourceToLoad)
	{
		// Load the resource
		Resource resource = Resource.Load(resourceToLoad);
		
		// Validate the prefab and show an appropriate error if invalid
		if(!resource.IsValid())
		{
			Print(("[SCR_ResourceHandler7RComponent: GenerateAndValidateResource] Resource is invalid: " + resourceToLoad), LogLevel.ERROR);
			return null;
		}
		
		// Return the resource
		return resource;
	}

	//------------------------------------------------------------------------------------------------
	EntitySpawnParams GenerateSpawnParameters(vector spawnPosition)
	{
		// Create a new set of spawn parameters
		EntitySpawnParams params = EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		
		// Assign the postion to those parameters
		params.Transform[3] = spawnPosition;
		
		// Return this set of spawn parameters
		return params;
	}
	
	//------------------------------------------------------------------------------------------------
	IEntity SpawnEntityOnPosition(ResourceName resourceToSpawn, vector spawnPosition)
	{
		// Generate template
		Resource resource = this.GenerateAndValidateResource(resourceToSpawn);
		
		if (!resource)
		{
			Print(("[S7R_ResourceHandlerComponent: SpawnEntityOnPosition] Unable to Load Resource " + resourceToSpawn), LogLevel.ERROR);
			return null;
		}

		//Generate spawn parameters and spawn group
		IEntity ent = GetGame().SpawnEntityPrefab(resource, null, this.GenerateSpawnParameters(spawnPosition));
		
		if (!ent)
			Print(("[S7R_ResourceHandlerComponent: SpawnEntityOnPosition] Unable to Spawn Resource " + resourceToSpawn), LogLevel.ERROR);
		
		return ent;
	}
}