from django.conf.urls import url
from django.urls import path, re_path
from django.views.generic import ListView, DetailView

from .models import InfoPost

from . import views

urlpatterns = [
    re_path(r'^$', views.index, name="index"),
    re_path(r'^news_add/$', views.create_news, name='news_add'),
    re_path(r"^posts/$", views.info_list, name='info_list'),
    re_path(r'^posts/(?P<slug>[\w-]+)/$', views.post, name='post'),
    re_path(r'^about/$', views.more, name='About'),
    re_path(r'^signup/$', views.signup, name='signup'),
    re_path(r'^account_activation_sent/$', views.account_activation_sent, name='account_activation_sent'),
    re_path(r'^activate/(?P<uidb64>[0-9A-Za-z_\-]+)/(?P<token>[0-9A-Za-z]{1,13}-[0-9A-Za-z]{1,20})/$', views.activate, name='activate'),
    re_path(r'^change_password/$', views.change_password, name='change_password'),
    re_path(r'^user/(?P<username>[0-9A-Za-z_\-]+)$', views.user_profile, name='user_profile'),
    re_path(r'^user_edit/(?P<username>[0-9A-Za-z_\-]+)$', views.edit_profile, name='user_profile_edit'),
]