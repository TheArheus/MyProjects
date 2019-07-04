from django.contrib import admin
from .models import InfoPost, UserProfile, PostComment

# Register your models here.

class PostAdmin(admin.ModelAdmin):
    prepopulated_fields = {"slug": ("title",)}

admin.site.register(InfoPost, PostAdmin)
admin.site.register(UserProfile)
admin.site.register(PostComment)
